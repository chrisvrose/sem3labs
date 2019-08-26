#include<stdio.h>
#define STACK_LEN 32


///Standard Stack implementation

typedef struct Stack{
	int top;
	int stack[STACK_LEN];
}Stack;

void SInit(Stack* stack){
	stack->top=-1;
}

int SPop(Stack* stack, int* returnVar){
	if(stack->top==-1){
	return 1;
	}
	else{
		*returnVar = stack->stack[stack->top];
		stack->top-=1;
		return 0;
	}
}



int SPush(Stack* stack, int element){
	if(stack->top == STACK_LEN-1){
		return 1;
	}
	else{
		stack->top+=1;
		stack->stack[stack->top] = element;
		return 0;
	}
}


///Program specific implementation


void SDisplay(Stack* stack){
	printf("Stack:\n");
	int i;
	for(i=stack->top;i>-1;i--){
		printf(":%d\n",stack->stack[i]);
	}
}

int SPopN(Stack* stack,int n){
	if( n-1 > stack->top){
		//fprintf(stderr,"E: Cannot Pop %d elements, only %d in array\n",n,stack->top+1);
		return 1;
	}
	else{
		int outVar;
		while(n!=0){
			if(SPop(stack,&outVar)){
				fprintf(stderr,"E:Error Popping\n");
			}
			printf("Popped:%d\n",outVar);
			n-=1;
		}
		return 0;
	}
}

///Return 1 if not enough elements
int S3FromTop(Stack* stack,int *y){
	Stack tempStack;int outVar,i;SInit(&tempStack);
	if(stack->top>=2){
		for(i=1;i<3;i++){
			SPop(stack,&outVar);
			SPush(&tempStack,outVar);
		}
		*y = stack->stack[stack->top];
		while(tempStack.top > -1){
			SPop(&tempStack,&outVar);
			SPush(stack,outVar);
		}
		return 0;
	}
	else{
		///Not enough items to check beneath
		return 1;
	}
}

///Return 1 if not enough space
int S3FromBottom(Stack* stack,int *y){
	if(stack->top>=2){
		///Assume Stacks have same length & >3, so push and pop must always work.
		Stack tempStack;int outVar;
		SInit(&tempStack);
		while(stack->top >= 3){
			SPop(stack,&outVar);
			SPush(&tempStack,outVar);
		}
		///Store in y
		*y = stack->stack[stack->top];
		///Restore
		while(tempStack.top > -1){
			SPop(&tempStack,&outVar);
			SPush(stack,outVar);
		}
		return 0;
	}
	else{
		///Error:Not enough items
		return 1;
	}
}


const char menu[] = "Options:\n1.Push\n2.Pop\n3.Display\n4.3rd from Top\n5. Pop N elements\n6.3rd from Bottom\n7.Exit";
int main(){
	Stack s1;SInit(&s1);
	int outVar, y;
	for(int a=0;(printf("%s\n:",menu),scanf("%d",&a))==1;){
		switch(a){
			case 1:
				printf("Enter element to push into stack\n:");
				scanf("%d",&outVar);
				if(!SPush(&s1,outVar)){
					printf("I:%d pushed into Stack\n",outVar);
				}else{
					fprintf(stderr,"E:Could not push: Stack overflow.\n");
				}
				break;
			case 2:
				printf("I:Popping element\n");
				if(!SPop(&s1,&outVar)){
					printf("Popped element:%d\n",outVar);
				}else{
					fprintf(stderr,"E:Could not pop: Stack underflow\n");
				}
				break;
			case 3:
				SDisplay(&s1);
				break;
			case 4:
				if(S3FromTop(&s1,&outVar)){
					fprintf(stderr,"E:Not enough elements\n");
					return 0;
				}
				y = outVar;
				printf("y = %d\n",y);
				break;
			case 5:
				printf("How many elements to pop?\n:");
				scanf("%d",&outVar);
				if(!SPopN(&s1,outVar)){
					printf("I:Popped %d elements\n",outVar);
				}else{
					fprintf(stderr,"E:Not enough elements\n");
				}
				break;
			case 6:
				if(S3FromBottom(&s1,&outVar)){
					fprintf(stderr,"E:Not enough elements\n");
					return 0;
				}
				y = outVar;
				printf("y = %d\n",y);
				break;
			case 7:
				return 0;
			default:
				fprintf(stderr,"E:Invalid choice\n");
		}
	}
	return 0;
}
