#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define SIZE 5
#define MODADD1(x) (((x)+1)%SIZE)


#define MUCHHUNGER 1

//#define

///Chopsticks
sem_t chopsticks[SIZE],mutex;
///State of each philosopher
char state[SIZE];
#define THINK 0
#define HUNGER 1
#define CONSUME 2


void* dinerDoSomething(void* arg){
	int identity = (int)arg;
	int outVar1,outVar2;
	printf("%d\n",identity);
	for(int i=0;i<MUCHHUNGER;i++){
		printf("P%d: hunger\n",identity);
		state[i] = HUNGER;
		sem_wait(&mutex);
		sem_getvalue(chopsticks+i,&outVar1);
		sem_getvalue(chopsticks+MODADD1(i),&outVar2);
		if(outVar1==1&&outVar2==1){
			sem_wait(chopsticks+i);
			sem_wait(chopsticks+MODADD1(i));
			state[identity]= CONSUME;
			printf("P%d:consume\n",identity);
			sem_post(chopsticks+i);
			sem_post(chopsticks+MODADD1(i));
			state[identity]=THINK;
		}
		sem_post(&mutex);
	}
	return NULL;
}


int main(){
	sem_init(&mutex,0,1);
	pthread_t philosopher[SIZE];
	for(int i=0;i<SIZE;i++){
		sem_init(chopsticks+i,0,1);
		state[i] = THINK;
	}
	for(int i=0;i<SIZE;i++){
		pthread_create(philosopher+i,NULL,dinerDoSomething,(void*)i);
	}

	for(int i=0;i<SIZE;i++){
		pthread_join(philosopher[i],NULL);
	}

	return 0;
}
