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


///Program Specific


int main(){
    Stack s;SInit(&s);
    char input[64]={};int l=0,c=0;
    char output[64]={};
    char buffer;
    scanf("%63[^\n]",input);

    while(input[l++]);
    for(int i=0;i<l;i++){
        if(input[i]==' '||input[i]==0){
            while(!SEmpty(&s)){
                SPop(&s,&buffer);
                output[c++]=buffer;
            }
            output[c++]=' ';
        }else{
            SPush(&s,input[i]);
        }
    }
    output[c]=0;


    printf("%s\n",output,l);
    return 0;
}