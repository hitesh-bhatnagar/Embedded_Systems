// 	Multi threaded logger

/*
Multiple threads write logs into a shared file
if we don't use a mutex -> logs overlap/corrupt
with a mutex -> logs are consistent
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


#define num_threads 3
#define num_logs 5

pthread_mutex_t lock;	// global mutex

// Thread function
void* write_logs(void* arg){
	int thread_id = *((int*)arg);

	for(int i = 0; i< num_logs; i++){
		pthread_mutex_lock(&lock);			// lock before writing to a file

		FILE *file = fopen("logs.txt", "a");
		if(file == NULL){
			perror("Error opening log file");
			pthread_mutex_unlock(&lock);
			pthread_exit(NULL);
		}

		fprintf(file, "Thread %d: Log entry %d\n", thread_id, i+1);
		fclose(file);

		pthread_mutex_unlock(&lock);	// unlock after writin

		usleep(500000);
	}
	return NULL;
}

int main() {
	pthread_t threads[num_threads];
	int thread_ids[num_threads];

	pthread_mutex_init(&lock ,NULL);

	int i = 0;
	while(i++ < num_threads){
		thread_ids[i] = i+1;
		pthread_create(&threads[i], NULL, write_logs, &thread_ids[i]);
		
	}

	// wait for all threads
	for(int i = 0; i < num_threads; i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&lock);

	printf("Los written to log.txt");
	return 0;
}
