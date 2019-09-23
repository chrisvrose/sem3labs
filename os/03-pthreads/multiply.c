
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
	threadInput *given = (threadInput *)arg;
	int k;
	given->matrices->matriSet[2][given->r][given->c] = 0;
	for(int k=0;k<DIM;k++){
		given->matrices->matriSet[2][given->r][given->c] += given->matrices->matriSet[0][given->r][k]*given->matrices->matriSet[1][k][given->c];
	}
	pthread_exit(0);
}

int main(){
	pthread_t threads[DIM][DIM];
	matrixSet matrixset=(matrixSet){};
	threadInput threadinput[DIM][DIM];
	printf("Enter %dx%d matrix 1\n:",DIM,DIM);
	for(int i=0;i<DIM;i++){
		for(int j=0;j<DIM;j++){
			scanf("%d",&(matrixset.matriSet[0][i][j]));
		}
	}

	printf("Enter %dx%d matrix 2\n:",DIM,DIM);
	for(int i=0;i<DIM;i++){
		for(int j=0;j<DIM;j++){
			scanf("%d",&(matrixset.matriSet[1][i][j]) );
		}
	}

	///Calc
	for(int i=0;i<DIM;i++){
		for(int j=0;j<DIM;j++){
			threadinput[i][j].matrices = &matrixset;
			threadinput[i][j].r = i;
			threadinput[i][j].c = j;
			pthread_create(&threads[i][j],NULL,matrixMult,(void*)&threadinput[i][j]);
		}
	}
	///Print
	printf("Result:\n");
	for(int i=0;i<DIM;i++){
		for(int j=0;j<DIM;j++){
			pthread_join(threads[i][j],NULL);
			printf("%d ",matrixset.matriSet[2][i][j]);
		}
		printf("\n");
	}
	return 0;
}
