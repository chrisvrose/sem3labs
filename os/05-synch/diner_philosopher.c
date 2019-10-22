#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define SIZE 5
#define MODADD1(x) (((x) + 1) % SIZE)

#define MUCHHUNGER 1

//#define

///Chopsticks
sem_t chopsticks[SIZE], mutex1, mutex2;
///State of each philosopher
char state[SIZE];
#define THINK 0
#define HUNGER 1
#define CONSUME 2

int whenToStart = 1;

void* dinerDoSomething(void* arg)
{
    while (whenToStart)
        ;
    int identity = (int)arg;
    int outVar1 = 0, outVar2 = 0;
    //printf("%d\n",identity);
    for (int i = 0; i < MUCHHUNGER; i++) {
        printf("P%d: hunger\n", identity);
        state[i] = HUNGER;

        sem_wait(&mutex1);
        while (outVar1 != 1 || outVar2 != 1) {
            sem_getvalue(chopsticks + identity, &outVar1);
            sem_getvalue(chopsticks + MODADD1(identity), &outVar2);
        }
        sem_wait(chopsticks + identity);
        sem_wait(chopsticks + MODADD1(identity));
        printf("P%d:picking up %d,%d\n", identity, identity, MODADD1(identity));
        sem_post(&mutex1);

        state[identity] = CONSUME;
        printf("P%d:consume\n", identity);

        sem_wait(&mutex2);
        printf("P%d: putting down %d,%d\n", identity, identity, MODADD1(identity));
        sem_post(chopsticks + identity);
        sem_post(chopsticks + MODADD1(identity));
        state[identity] = THINK;

        sem_post(&mutex2);
    }
    return NULL;
}

int main()
{
    sem_init(&mutex1, 0, 1);
    sem_init(&mutex2, 0, 1);
    pthread_t philosopher[SIZE];
    for (int i = 0; i < SIZE; i++) {
        sem_init(chopsticks + i, 0, 1);
        state[i] = THINK;
    }
    for (int i = 0; i < SIZE; i++) {
        pthread_create(philosopher + i, NULL, dinerDoSomething, (void*)i);
    }
    whenToStart = 0;
    for (int i = 0; i < SIZE; i++) {
        pthread_join(philosopher[i], NULL);
    }

    return 0;
}
