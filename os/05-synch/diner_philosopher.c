#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define SIZE 5
#define MODADD1(x) (((x)+1)%SIZE)

///Chopsticks
sem_t chopsticks[SIZE];
///State of each philosopher
char state[SIZE];


int main(){
	for(int i=0;i<SIZE;i++) sem_init(chopsticks+i,0,1);
	return 0;
}
