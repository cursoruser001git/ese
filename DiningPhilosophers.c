#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5  // number of philosophers
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N];                  // state of each philosopher
pthread_mutex_t mutex;         // global mutex for critical section
pthread_mutex_t chopstick[N];  // one mutex per chopstick

void test(int i) {
    if (state[i] == HUNGRY &&
        state[(i + 4) % N] != EATING &&
        state[(i + 1) % N] != EATING) {
        state[i] = EATING;
        printf("Philosopher %d takes chopsticks %d and %d\n", i + 1, (i + 4) % N + 1, i + 1);
        printf("Philosopher %d is Eating\n", i + 1);
        pthread_mutex_unlock(&chopstick[i]);
    }
}

void take_chopsticks(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is Hungry\n", i + 1);
    test(i);
    pthread_mutex_unlock(&mutex);
    pthread_mutex_lock(&chopstick[i]); // wait until philosopher can eat
}

void put_chopsticks(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = THINKING;
    printf("Philosopher %d puts down chopsticks %d and %d\n", i + 1, (i + 4) % N + 1, i + 1);
    printf("Philosopher %d is Thinking\n", i + 1);
    test((i + 4) % N);
    test((i + 1) % N);
    pthread_mutex_unlock(&mutex);
}

void *philosopher(void *num) {
    int i = *(int *)num;
    while (1) {
        sleep(1);
        take_chopsticks(i);
        sleep(2);
        put_chopsticks(i);
    }
}

int main() {
    pthread_t thread_id[N];
    int phil_num[N];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&chopstick[i], NULL);
        pthread_mutex_lock(&chopstick[i]);
        phil_num[i] = i;
    }

    for (int i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil_num[i]);
        printf("Philosopher %d is Thinking\n", i + 1);
    }

    for (int i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    return 0;
}

