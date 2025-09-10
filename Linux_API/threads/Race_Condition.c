// if two threads try to write to the same file or variable at the same time --> corruption

#include <stdio.h>
#include <pthread.h>

int count = 0;	// shared variable

void* increment(void* arg){
	for(int i = 0; i < 100000; i++) count++;
	return NULL;
}


int main(void){
	pthread_t t1, t2;
	pthread_create(&t1, NULL , increment, NULL);
	pthread_create(&t2, NULL, increment, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("Final count = %d\n", count);

	return 0;
}
