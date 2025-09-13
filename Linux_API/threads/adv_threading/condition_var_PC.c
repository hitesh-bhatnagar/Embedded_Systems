/*
##				Condition varaibles (producer-consumer)

conditional var (pthread_cond_t) is used when one thread must wait for a contion and another thread signals it.

works with a mutex:		
	*	pthread_cond_wait(&cond, &mutex) -> atomically unlocks mutex and waits
	*	pthread_cond_signal(&cond) -> wakes up one waiting thread
	*	pthread_cond_broadcast(&cond) -> wakes all waiting threads

EXAMPLE:	
		producer puts items into a buffer
		consumder takes items out
		consumers wait if buffer empty. Producwes signal when new item available

*/	

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#define size  5

int buffer[size];
int count = 0;	//number of items in buffer

pthread_mutex_t lock;
pthread_cond_t not_empty, not_full;

void* producer(void* arg){

	for(int i = 0; i < 10; i++){
		pthread_mutex_lock(&lock);

		while(count == size) pthread_cond_wait(&not_full, &lock);	// wait if buffer full

		buffer[count++] = i;
		printf("Producer produced: %d\n", i);

		pthread_cond_signal(&not_empty);		// signal consumer
		pthread_mutex_unlock(&lock);


	}
	return NULL;
}

void* consumer(void* arg){
	for(int i = 0; i < 10; i++){
		pthread_mutex_lock(&lock);

		while(count == 0) pthread_cond_wait(&not_empty, &lock);	// wait if buffer empty

		int item = buffer[--count];
		printf("Consumer consumed : %d\n", item);
		pthread_cond_signal(&not_full);	// signal producer

	}
	return NULL;
}


int main(){
	pthread_t prod, cons;

	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&not_empty, NULL);
	pthread_cond_init(&not_full, NULL);

	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);

	pthread_join(prod, NULL);
	pthread_join(cons, NULL);


	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&not_empty);
	pthread_cond_destroy(&not_full);
	return 0;
}
