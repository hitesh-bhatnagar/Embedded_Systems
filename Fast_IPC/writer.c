#include <stdio.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/shm.h>

int main(void){
	// project id is 65-
	key_t key = ftok("shmfile", 65); // generates unique key for the shared memory segment
	
	int shmid = shmget(key, 1024, 0666|IPC_CREAT);
	char *str = (char*) shmat(shmid, (void*)0, 0);

	strcpy(str, "Hello from shared memory");
	printf("Data written \n");

	shmdt(str);
	return 0;
}
