
#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<pthread.h>

#include<unistd.h>

#define DIM 4

typedef struct matrixSet{
	int matriSet[3][DIM][DIM];
}matrixSet;

typedef struct threadInput{
	matrixSet* matrices;
	int r,c;
}threadInput;

void* matrixMult(void* arg){
	threadInput *given = (threadInput)arg;
	int k;
	for(
	return NULL;
}

int main(){
	pthread_t threads[DIM][DIM];
	matrixSet matrixset=(matrixSet){};
	threadInput threadinput[DIM][DIM];
	for(int i=0;i<DIM;i++){
		for(int j=0;j<DIM;j++){
			threadinput[i][j].matrices =matrixset;
			threadinput[i][j].r = i;
			threadinput[i][j].c = j;
			pthread_create(&threads[i][j],NULL,matrixMult,(void*)&threadinput[i][j]);
		}
	}
	return 0;
}
