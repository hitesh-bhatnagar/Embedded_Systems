//			Counter with shared memory + semaphore

#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/ipc.h>

#define SHM_KEY 1234
#define SEM_KEY 5678

// create semaphore 
int create_semaphore(key_t key){
	return semget(key, 1, 0666 | IPC_CREAT);
	
}
// set initial value
void set_sem_value(int semid, int val){
	union semun{
		int val;
	} sem_attr;

	sem_attr.val = val;
	semctl(semid, 0, SETVAL, sem_attr);
}

// wait (lock)
void sem_wait_custom(int semid){
	struct sembuf sb = {0, -1, 0};
	semop(semid, &sb, 1);
}

// signal (unlock )
void sem_signal_custom(int semid){
	struct sembuf sb = {0, 1, 0};
	semop(semid, &sb, 1);
}

int main(){
	// create shared memory
	int shmid = shmget(SHM_KEY, sizeof(int), 0666 | IPC_CREAT);
	int *counter = (int*)shmat(shmid, NULL, 0);

	// create semaphore
	int semid = create_semaphore(SEM_KEY);
	set_sem_value(semid, 1);	// start unlocked

	for(int i = 0; i < 5; i++){
		sem_wait_custom(semid);		// lock 
		(*counter)++;		// critical section
		printf("Process %d incremented counter to %d \n", getpid(), *counter);
		sem_signal_custom(semid);	// unlock
		sleep(1);
	}

	shmdt(counter);
	return 0;
}
