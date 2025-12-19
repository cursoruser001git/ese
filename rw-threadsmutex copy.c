#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex, wrt;
int read_count = 0;
int data = 0;

void* reader(void* arg) {
    int id = *((int*)arg);

    while (1) {
        pthread_mutex_lock(&mutex);
        read_count++;
        if (read_count == 1)
            pthread_mutex_lock(&wrt);
        pthread_mutex_unlock(&mutex);

        printf("Reader %d is reading data = %d\n", id, data);
        sleep(1);

        pthread_mutex_lock(&mutex);
        read_count--;
        if (read_count == 0)
            pthread_mutex_unlock(&wrt);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
}

void* writer(void* arg) {
    int id = *((int*)arg);

    while (1) {
        pthread_mutex_lock(&wrt);
        data++;
        printf("Writer %d is writing data = %d\n", id, data);
        sleep(1);
        pthread_mutex_unlock(&wrt);

        sleep(1);
    }
}

int main() {
    pthread_t rtid[5], wtid[2];
    int r_id[5] = {1, 2, 3, 4, 5};
    int w_id[2] = {1, 2};

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&wrt, NULL);

    for (int i = 0; i < 5; i++)
        pthread_create(&rtid[i], NULL, reader, &r_id[i]);
    for (int i = 0; i < 2; i++)
        pthread_create(&wtid[i], NULL, writer, &w_id[i]);

    for (int i = 0; i < 5; i++)
        pthread_join(rtid[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(wtid[i], NULL);

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&wrt);

    return 0;
}

