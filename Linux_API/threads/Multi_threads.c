#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void* worker(void* arg){
	int id = *((int*) arg);
	printf("Worker %d is running\n", id);
	return NULL;
}

int main(){

	pthread_t threads[3];
	int ids[3] = {1,2,3};

	for(int i = 0; i < 3; i++) pthread_create(&threads[i], NULL, worker, &ids[i]);

	for(int i = 0; i < 3; i++) pthread_join(threads[i], NULL);

	printf("All threads finished \n");
		
	return 0;
}
