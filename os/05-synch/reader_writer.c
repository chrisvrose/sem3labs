#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define TIMES 10

#define RANDMAX 20

sem_t mutex,wrt;
int readCount=0;
int whenToStart=1;

char fn[]="text.txt";

void* reader(void* arg){
	while(whenToStart);
	char buffer[RANDMAX];
	for(int i=0;i<TIMES;i++){
		sem_wait(&mutex);
		readCount++;
		if(readCount==1){
			sem_wait(&wrt);
		}
		sem_post(&mutex);
		//Read
		FILE *fp;
		fp = fopen(fn,"r");
		fscanf(fp,"%99[^\n]",buffer);
		printf("R:%s\n",buffer);
		fclose(fp);
		//Done read

		sem_wait(&mutex);
		readCount--;
		if(readCount==0){
			sem_post(&wrt);
		}
		sem_post(&mutex);
		
	}
	return NULL;
}

void* writer(void* arg){
	while(whenToStart);
	for(int i=0;i<TIMES;i++){
		sem_wait(&wrt);
		//Write
		FILE *fp;
		fp = fopen(fn,"w");
		int insertVal = random()%RANDMAX;
		fprintf(fp,"%d",insertVal);
		fclose(fp);
		//dataSegment = random()%RANDMAX;
		printf("W:%d\n",insertVal);
		sem_post(&wrt);
	}
	return NULL;
}


int main(){
	pthread_t w,r1,r2;
	sem_init(&mutex,0,1);
	sem_init(&wrt,0,1);
	pthread_create(&w,NULL,writer,NULL);
	pthread_create(&r1,NULL,reader,NULL);
	pthread_create(&r2,NULL,reader,NULL);
	whenToStart=0;

	pthread_join(w,NULL);
	pthread_join(r1,NULL);
	pthread_join(r2,NULL);
}
