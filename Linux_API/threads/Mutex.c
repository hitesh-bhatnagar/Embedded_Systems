// Fixing Race Condition

#include <stdio.h>
#include <pthread.h>

int count = 0;
pthread_mutex_t lock;

void* increment(void* arg){
	for(int i = 0; i < 100000; i++){
		pthread_mutex_lock(&lock);		// lock before using shared variable
		count++;
		pthread_mutex_unlock(&lock);	// unlock after use;
	}
	return NULL;
} 


int main(){
	pthread_t t1, t2;
	pthread_mutex_init(&lock, NULL);

	pthread_create(&t1, NULL, increment, NULL);
	pthread_create(&t2, NULL, increment, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&lock);
	printf("Final count = %d\n", count);			// always 200000
	

	return 0;
}
