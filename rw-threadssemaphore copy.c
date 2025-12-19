#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt;   
int read_count = 0; 
int data = 0;       

void* reader(void* arg) {
    int id = *((int*)arg);

    while (1) {
        sem_wait(&mutex);        
        read_count++;
        if (read_count == 1)     
            sem_wait(&wrt);
        sem_post(&mutex);

        printf("Reader %d is reading data = %d\n", id, data);
        sleep(1);

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0)     
            sem_post(&wrt);
        sem_post(&mutex);

        sleep(1);
    }
}

void* writer(void* arg) {
    int id = *((int*)arg);

    while (1) {
        sem_wait(&wrt);
        data++;  
        printf("Writer %d is writing data = %d\n", id, data);
        sleep(1);
        sem_post(&wrt);

        sleep(1);
    }
}

int main() {
    pthread_t rtid[5], wtid[2];
    int r_id[5] = {1, 2, 3, 4, 5};
    int w_id[2] = {1, 2};

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (int i = 0; i < 5; i++)
        pthread_create(&rtid[i], NULL, reader, &r_id[i]);
    for (int i = 0; i < 2; i++)
        pthread_create(&wtid[i], NULL, writer, &w_id[i]);

    for (int i = 0; i < 5; i++)
        pthread_join(rtid[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(wtid[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}

