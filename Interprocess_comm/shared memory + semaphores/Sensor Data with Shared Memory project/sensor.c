#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "shmdata.h"

//semaphore operations
void sem_lock(int semid){
    struct sembuf sb = {0, -1, 0};  // P operation (wait/down) is used to requres a resource by decrementing semaphore value. If the value < 0 , the process blocks until the resource is available
    semop(semid, &sb, 1);

}

void sem_unlock(int semid){
    struct sembuf sb = {0, 1, 0};   // v operation (signal/up) is used to release a resource by incrementing the semaphore value, and if there are blovked processes waiting for that resource, one of them is unblocked
    semop(semid, &sb, 1);
}

int main(){
    // create shared memory
    int shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0666 | IPC_CREAT)
    if(shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // attach
    struct shmseg* shmp = shmat(shmid, NULL, 0);
    if(shmp == (void*)-1){
        perror("shmat");
        exit(1);
    }

    // Create semaphore
    int semid = semget(SEM_KEY, 1, 0666 | IPC_CREAT);
    if(semid == -1){
        perror("semget");
        exit(1);
    }
    semctl(semid, 0, SETVAL, 1);    // initialize to 1
}