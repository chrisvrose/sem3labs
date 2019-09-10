#include<stdio.h>

#include<stdlib.h>

#define cQSIZE 4
#define strSIZE 64

#define ADDONE(x) (((x)+1)%cQSIZE)

typedef struct cQueue{
	int f;
	int r;
	char messages[cQSIZE][strSIZE];
}cQ;

void cQInit(cQ *cq){
	cq->f=cq->r=-1;
}

//
//int ModAddCQ(int add1,int add2){

int cQIsEmpty(cQ *cq){
	return cq->f==-1;
}

int cQEnQ(cQ *cq,char *input){
	if(cQIsEmpty(cq)){//if empty, create
		cq->f=0;
		cq->r=-1;
	}
	else if( ADDONE(cq->r) == cq->f ){
		return 1;//Full
	}
	//printf("I:EQ(%s,%d,%d)\n",input,cq->f,cq->r);
	cq->r = ADDONE(cq->r);
	//Copy the string item
	int i=0;
	for(i=0;input[i]!=0;i++) cq->messages[cq->r][i] = input[i];
	cq->messages[cq->r][i]=0;
	return 0;
}


int cQDeQ(cQ *cq,char* outVar){
	if(cq->f==-1){//Empty
		return 1;
	}
	//Copy
	int i=0;
	for(i=0;cq->messages[cq->f][i];i++) outVar[i] = cq->messages[cq->f][i];
	outVar[i]=0;
	//Setting new rear
	if(cq->f==cq->r){//Unset Queue
		cq->f=-1;
	}else{
		cq->f = ADDONE(cq->f);
	}
	return 0;
}

//Program specific

void cQDisplay(cQ *cq){
	//for(int i=cq->f;i != cq->r;ADDONE(i)){
	//	printf(":%s\n",cq->messages[i]);
	//}
	if(!cQIsEmpty(cq)){
		int i;
		for(i=cq->f;i!=cq->r; i=ADDONE(i) ){
			printf(": %s\n",cq->messages[i]);
		}
		printf(": %s\n",cq->messages[i]);
	}
}

int main(){
	char menu[] = "1.Enqueue\n2.Dequeue\n3.Display\n4.Exit";
	cQ cq,*cqp;cqp = &cq;cQInit(cqp);
	char bufferVar[strSIZE];
	for(int a=0;(printf("%s\n:",menu),fflush(stdin),scanf("%d",&a)==1);){
		switch(a){
			case 1:
				printf("Enter message\n:");
				fflush(stdin);
				scanf(" %63[^\n]",bufferVar);
				if(!cQEnQ(cqp,bufferVar))
					printf("Enqueued successfully\n");
				else
					printf("E: Could not enqueue\n");
				break;
			case 2:
				if(!cQDeQ(cqp,bufferVar))
					printf("Dequeued successfully\n");
				else
					printf("E: Could not dequeue\n");
				break;
			case 3:
				cQDisplay(cqp);
				break;
			case 4:
				printf("...\n");
				return 0;
				break;
			default:
				printf("Invalid input\n");
		}
	}
	return 0;
}

