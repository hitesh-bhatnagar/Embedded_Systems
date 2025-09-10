#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* mythread(void* arg){
	printf("Hello from thread! Argument = %s\n", (char*) arg);
	return NULL;
}

int main(){
	pthread_t tid;
	pthread_create(&tid, NULL, mythread, "thread-1");		// create thread
	pthread_join(tid, NULL);		// wait for thread to finish
	printf("Main thread finished\n");

	return 0;
}
