#include<stdio.h>
#include<ctype.h>

#define STACK_LEN 32


///Standard Stack implementation

typedef struct Stack{
	int top;
	char stack[STACK_LEN];
}Stack;

void SInit(Stack* stack){
	stack->top=-1;
}

int SPop(Stack* stack, char* returnVar){
	if(stack->top==-1){
	return 1;
	}
	else{
		*returnVar = stack->stack[stack->top];
		stack->top-=1;
		return 0;
	}
}



int SPush(Stack* stack, char element){
	if(stack->top == STACK_LEN-1){
		return 1;
	}
	else{
		stack->top+=1;
		stack->stack[stack->top] = element;
		return 0;
	}
}

int SPeek(Stack* stack,char *element){
	if(stack->top==-1)
		return 1;
	else{
		*element = stack->stack[stack->top];
		return 0;
	}
}


///1 if empty
int SEmpty(Stack *stack){
	return stack->top==-1;
}



///Program specific implementation

char getPriority(char token){
	if(token=='('||token==')')
		return 0;
	if(token=='+'||token=='-')
		return 1;
	if(token=='*'||token=='/'||token=='%')
		return 2;
	///All else
	return 3;
}

int infixToPostfix(char* inputFix,char *outputFix){
	Stack stack;SInit(&stack);int j=0;
	char outVar1,outVar2;
	for(int i=0;inputFix[i]!=0;i++){
		if(isalnum(inputFix[i])){//literal
			outputFix[j++]=inputFix[i];
		}else if(getPriority(inputFix[i])==2&&inputFix[i]!=')'){//Opening
			SPush(&stack,inputFix[i]);
		}else if(inputFix[i]==')'){
			SPop(&stack,&outVar1);
			while(outVar1!='('){
				outputFix[j++]=(char)outVar1;
				SPop(&stack,&outVar1);
			}
		}
		else{
			int ret = SPeek(&stack,&outVar1);
			if(!SEmpty(&stack)){
				while(getPriority((char)outVar1)>=getPriority(inputFix[i])&&!SEmpty(&stack)){
					if(SPop(&stack,&outVar2)){
						//outVar1='(';
						fprintf(stderr,"Something went wrong");
					}else{
						outputFix[j++]=(char)outVar2;
					}
				}
			}
			SPush(&stack,inputFix[i]);
			
		}
	}
	while(!SEmpty(&stack)){
		int outVar1;
		SPop(&stack,&outVar1);
		outputFix[j++]=outVar1;
	}
	outputFix[j]=0;
	return 0;
}




const char menu[] = "Options:\n1.Enter expression\n2.Exit";
int main(){
	Stack s1;SInit(&s1);
	int outVar, y;char inputString[20],outputString[20];
	printf("%s\n",menu);
	for(int a=0;(printf("Command\n:",menu),scanf("%d",&a))==1;){
		switch(a){
			case 1:
				printf("Enter expression\n:");
				scanf(" %s",inputString);
				fflush(stdin);
				//printf(" %s",inputString);
				if(!infixToPostfix(inputString,outputString)){
					printf("Expression: %s\n",outputString);
				}else{
					fprintf(stderr,"E: Could not convert\n");
				}
				break;
			case 2:
				printf("I:Exiting\n");
				return 0;
			default:
				fprintf(stderr,"E:Invalid choice\n");
				return 1;
		}
	}
	return 0;
}
