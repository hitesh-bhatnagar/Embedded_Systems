#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 3
#define NUM_LOGS 5

pthread_mutex_t lock; // global mutex

// Thread function
void* write_logs(void* arg) {
    int thread_id = *((int*)arg);

    for (int i = 0; i < NUM_LOGS; i++) {
        pthread_mutex_lock(&lock);   // lock before writing to file

        FILE *f = fopen("logs.txt", "a");
        if (f == NULL) {
            perror("Error opening log file");
            pthread_mutex_unlock(&lock);
            pthread_exit(NULL);
        }

        fprintf(f, "Thread %d: Log entry %d\n", thread_id, i+1);
        fclose(f);

        pthread_mutex_unlock(&lock); // unlock after writing

        usleep(100000); // simulate some work
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    pthread_mutex_init(&lock, NULL);

    // create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, write_logs, &thread_ids[i]);
    }

    // wait for all threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("Logs written to logs.txt\n");
    return 0;
}
