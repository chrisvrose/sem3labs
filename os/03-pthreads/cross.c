
#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<pthread.h>

#include<unistd.h>

typedef struct Vector{
	int matrix[3][3];	///[3 arrays][3D]
}Vector;

typedef struct threadInput{
	Vector* vector;
	int dim;
}threadInput;

void* vectorCross(void* arg){
	threadInput *given = (threadInput *)arg;
	given->vector->matrix[2][given->dim] = 0;
	for(int k=0;k<3;k++){
		given->vector->matrix[2][k] = given->vector->matrix[0][(k+1)%3] * given->vector->matrix[1][(k+2)%3] \
		- given->vector->matrix[0][(5-k)%3] * given->vector->matrix[1][(4-k)%3];
	}
	pthread_exit(0);
}

int main(){
	pthread_t threads[3];
	Vector vector;
	threadInput threadinput[3];
	printf("Enter 3d vector 1:\n");
	for(int i=0;i<3;i++){
		scanf("%d",vector.matrix[0]+i);
	}
	printf("Enter 3d vector 1:\n");
	for(int i=0;i<3;i++){
		scanf("%d",vector.matrix[1]+i);
	}

	///Calc
	for(int i=0;i<3;i++){
			threadinput[i].vector = &vector;
			threadinput[i].dim = i;
			pthread_create(&threads[i],NULL,vectorCross,(void*)&threadinput[i]);
	}
	///Print
	printf("Result:\n");
	for(int i=0;i<3;i++){
		pthread_join(threads[i],NULL);
		printf("%d ",vector.matrix[2][i]);
	}
	printf("\n");
	return 0;
}