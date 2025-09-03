#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdlib.h>

int log_fd;     // file descriptor for logging
int pipefd[2];  // pipe for IPC
pid_t children[2];  // store child PIDs

volatile sig_atomic_t running = 1;      // flag for signal handling

void log_pid(pid_t pid, const char* type){
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%s PID: %d\n", type, pid);
    write(log_fd, buffer, strlen(buffer))
}

// Signal handler for Ctrl + C

void handle_sigint(int sig){
    printf("\n Shutting down safely... \n");
    running = 0;

    // kill children
    for(int i = 0; i < 2; i++){
        if(children[i] > 0){
            kill(children[i], SIGTERM);
            printf("Killed child: %d\n", children[i]);
        }
    }

    close(log_fd);
    exit(0);
}


// Thread function to monitor CPU usage

void* monitor_cpu(void* arg){
    while(running){
		double usage = get_cpu_usage();
		if(usage >= 0) printf("CPU usage : %.2f%%\n", usage);
		sleep(2);
    }
    return NULL;
}


double get_cpu_usage(){
    static long prev_idle = 0, prev_total = 0;
    long user, nice, system, idle, iowait, irq, softirq, steal;

    FILE* file = fopen("/proc/stat", "r");
    if(!file) return -1;

	fscanf(file, "cpu %ld %ld %ld %ld %ld %ld %ld %ld",
	       &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);
	fclose(file);

	long idle_time = idle + iowait;
	long non_idle = user + nice + system + irq + softirq + steal;
	long total = idle_time + non_idle;

	long totalid = total - prev_total;
	long idled = idle_time - prev_idle;

	prev_total = total;
	prev_idle = idle_time;


	if(totalid == 0) return 0.0;
	return ((double)(totalid - idled)/ totalid)* 100.0;

}


void create_children(){
	for(int i= 0; i < 2; i++){
		pid_t pid = fork();
		if(pid == 0) {
			close(pipefd[1]);
			char msg[50];

			read(pipefd[0], msg, sizeof(msg));
			printf("Child %d received: %s\n", getpaid(), msg);
			sleep(5);
			exit(0);

		}else if(pid > 0){

			children[i] = pid;
			log_pid(pid, "Child");
		}else{
			perror("fork");
			exit(1);
		}
	}
}


int main(void){
	signal(SIGINT, handle_sigint);

	srand(getpid());

	// open file
	log_fd = open("process_log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(log_fd < 0){
		perror("open");
		exit(1);
	}

	// Log parent PID
	log_pid(getpid(), "Parent");
	printf("Parent PID: %d\n", getpid());

	// Create pipe

	if(pipe(pipefd) == -1){
	    perror("pipe");
		exit(1);
	}

	// Create children
	create_children();

	// Send Start message
	close(pipefd[0]);   // close read end
	char *msg = "Start task";
	for(int i = 0; i < 2; i++){
		write(pipefd[1], msg, strlen(msg)+1);
	}


	// Create monitor thread
	pthread_t monitor_thread;
	pthread_create(&monitor_thread, NULL, monitor_cpu, NULL);

	// wait for children
	for(int i = 0; i < 2; i++){
		waitpid(children[i], NULL, 0);
	}

	running  = 0;
	pthread_join(monitor_thread, NULL);
	close(log_fd);

	printf("Exiting Now");
	return 0;
	
}
