#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>


int log_fd;		// File descriptor
int pipefd[2];		// Pipe for IPC
pid_t children[2];		// store children PIDs/


volatile sig_atomic_t running = 1;			// Flag for signal handling

// Function to log PIDs into file

void log_pid(pid_t pid, const char* type){
	char buffer[100];
	snprintf(buffer, sizeof(buffer), "%s PID : %d\n", type, pid);
	write(log_fd, buffer, strlen(buffer));

	
}


// signal handler for Ctrl+C

void handle_sigint(int sig){
	printf("\n Shutting down... \n");
	running = 0;

	// Kill children

	for(int i = 0; i < 2; i++){
		if(children[i] > 0){
			kill(children[i], SIGTERM);
			printf("Killed child with PID %d\n", children[i]);
		}
	}

	close(log_fd);
	exit(0);
}



double cpu_usage(){
	static long prev_idle = 0, prev_total = 0;
	long user, nice, sys, idle, iowait, irq, softirq, steal;

	FILE* file = fopen("/proc/stat", "r");
	if(!file) return -1;

    fscanf(file, "cpu %ld %ld %ld %ld %ld %ld %ld %ld",
           &user, &nice, &sys, &idle, &iowait, &irq, &softirq, &steal);
           
    fclose(file);

    
	long idle_time = idle + iowait;
	long non_idle_time = user + sys + irq + softirq + steal;
	long total = idle_time + non_idle_time;

	long totald = total - prev_total;
	long idled = idle_time - prev_idle;

	prev_total = total;
	prev_idle = idle_time;

	if(totald == 0) return 0.0;

	return ((double)(totald - idled)/totald) * 100.0;
	
}

// Thread function to monitor CPU usage
void* monitor_cpu(void* arg){
	
	while(running){
		double usage = cpu_usage();
		if(usage >= 0) printf("CPU Usage : %.2f%%\n", usage);
		sleep(2);
	}

	return NULL;
}

// create child process
void create_children(){
	for(int i = 0; i < 2; i++){

		// creating a new pipe for each child
		if(pipe(pipefd) == -1) {
			perror("pipe");
			exit(1);
		}
		
		pid_t pid = fork();
		if(pid == 0) {				// child 
			close(pipefd[1]);		// close write end
			char msg[100];
			read(pipefd[0], msg, sizeof(msg));
			printf("Child %d received : %s\n", getpid(), msg);
			close(pipefd[0]);	// closing read end after reading
			
			sleep(2);
			exit(0);

			
		}else if(pid > 0){			// parent
			children[i] = pid;
			log_pid(pid,"Child");

			close(pipefd[0]);
			char* msg = "Start Task";
			write(pipefd[1], msg, strlen(msg)+1);
			close(pipefd[1]);
			

			
		}else{
			perror("fork");
			exit(1);
		}
	}
}





int main(void){

	signal(SIGINT, handle_sigint);
	srand(getpid());

	// open log file

	log_fd = open("processing_log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(log_fd < 0){
		perror("open");
		exit(1);
	}

	// Log parent PID
	
	log_pid(getpid(), "Parent");
	printf("Parent PID : %d\n", getpid());


	// Create children
	create_children();


	// Create monitor thread

	pthread_t monitor_thread;
	pthread_create(&monitor_thread, NULL, monitor_cpu, NULL);

	// wait for children

	for(int i = 0; i < 2; i++) waitpid(children[i], NULL, 0);

	running = 0;
	pthread_join(monitor_thread, NULL);
	close(log_fd);

	printf("Exiting Now... \n");
	

	return 0;
}

