This is an alternative to condition variables:

	Use two semaphores:
		* empty (tracks free slots in buffer) (initially = buffer size)
		* full -> counts filled slots (intially = 0)

	Mutex is still needed to protect the buffer itself

	Producer: 
		* sem_wait(empty) ->	wait if buffer full
		* Add item
		* sem_post(full) -> signal consumer

	Consumer:
		* sem_wait(full) -> wait if buffer empty
		* Remove item
		* sem_post(empty) -> signal producer

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define buffer_size 5
int buffer[buffer_size];
int in = 0, out = 0;	//circular buffer indices

sem_t empty, full;
pthread_mutex_t lock;

void* producer(void* arg){
	for(int i = 0; i < 10; i++){
		sem_wait(&empty);
		pthread_mutex_lock(&lock);

		buffer[in] = i;
		printf("Produver produced %d at index %d\n", i, in);

		in = (in + 1) % buffer_size;

		pthread_mutex_unlock(&lock);
		sem_post(&full);

		usleep(100000);
		
	}
	return NULL;
}	

void* consumer(void* arg){
	for(int i = 0; i < 10; i++){
		sem_wait(&full);
		pthread_mutex_lock(&lock);

		int item = buffer[out];
		printf("Consumer consumer: %d from index %d\n", item, out);
		out = (out + 1) % buffer_size;

		pthread_mutex_unlock(&lock);
		sem_post(&empty);

		usleep(150000);
	}
	return NULL;

}

int main(){
	pthread_t prod, cons;

	sem_init(&empty, 0, buffer_size);
	sem_init(&full, 0, 0);
	pthread_mutex_init(&lock, NULL);

	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);

	pthread_join(prod, NULL);
	pthread_join(cons, NULL);

	sem_destroy(&empty);
	sem_destroy(&full);
	pthread_mutex_destroy(&lock);

	return 0;
}
