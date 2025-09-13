/*
semaphore = integer counter that controls access 

Types : 
	*	Binary semaphore (0/1)  ->  like mutex
	* 	counting semaphore ->	allows N threads to access resource

Functions (POSIX):	
		* sem_init(&sem, 0, value)
		* sem_wait(&sem) 	-> decrease counter (wait if 0)
		* sem_post(&sem)	->	increase counter (signal)
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void* worker(void* arg){
	int id = *((int*)arg);

	printf("Thread %d waiting .. \n", id);
	sleep(1);
	printf("Thread %d leaving critical section\n", id);

	sem_post(&sem);
	return NULL;
}

int main(){
	pthread_t threads[3];
	int ids[3] = {1,2,3};

	sem_init(&sem, 0, 1);

	for(int i = 0; i < 3; i++) pthread_create(&threads[i], NULL, worker, &ids[i]);

	for(int i = 0; i < 3; i++) pthread_join(threads[i], NULL);

	sem_destroy(&sem);

	return 0;
}
