#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int STATE[N];
sem_t mutex;
sem_t S[N];

void test(int i){
    if(
        STATE[i] == HUNGRY &&
        STATE[(i+N-1) % N] != EATING &&
        STATE [(i + 1) % N] != EATING
    )   {
            STATE[i] = EATING;
            sleep(1);
            printf("Philosopher - %d takes fork %d and %d.\n", i+1, (i+N-1)%N +1, i+1);
            printf("Philosopher - %d starts eating.\n", i+1);
            sem_post(&S[i]);
        }
}

void take_fork(int i){
    sem_wait(&mutex);
    STATE[i] = HUNGRY;
    printf("Philosopher - %d is hungry.\n", i+1);
    test(i);
    sem_post(&mutex);
    sem_wait(&S[i]);
}

void put_fork(int i){
    sem_wait(&mutex);
    STATE[i] = THINKING;
    printf("Philosopher - %d has put down fork %d and %d.\n", i+1, (i+N-1)%N +1, i+1);
    printf("Philosopher - %d is thinking.\n", i+1);
    test((i+N-1)%N);
    test((i+1)%N);
    sem_post(&mutex);
}

void* philosopher(void* num){
    int i = *(int*)num;
    while(1){
        sleep(1);
        take_fork(i);
        sleep(2);
        put_fork(i);
    }
}

int main(){
    int i;
    pthread_t tid[N];
    int phill[N];

    sem_init(&mutex, 0, 1);
    for(i = 0; i<N; i++){
        sem_init(&S[i], 0, 0);
        phill[i] = i;
    }
    for(i = 0; i<N; i++){
        pthread_create(&tid[i], NULL, philosopher, &phill[i]);
    }
    for(int i = 0; i<N; i++){
        pthread_join(tid[i], NULL);
    }
    return 0;
}