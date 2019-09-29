#include<stdio.h>

#include<stdlib.h>

#define STRLEN 64

typedef struct node{
	///For storing small data
	char data;
	struct node* next;
} node;

node* getNode(char data){
	node *newNode;
	//Only if successful, create data
	if(newNode = malloc(sizeof(node)) ){
		newNode->data = data;
	}
	return newNode;
}

//#define getData(x) ((x)->data))

///Get Data, and free
char freeNode(node *toFree){
	if(toFree==NULL){
		return -1;
	}else{
		char toReturn = toFree->data;
		free(toFree);
		return toReturn;
	}
}

//0 if no errors
node* insertFront(node* head,char data){

	node* newNode;
	if((newNode=getNode(data))==NULL){
		return NULL;
	}

	//Time to make a new one
	if(head==NULL){
		head = newNode;
		newNode->next = head;
		//return head;
	}//if theres other things too
	else{
		node* last;
		///Get last
		for(last=head;last->next!=head;last=last->next);
		last->next = newNode;
		newNode->next = head;
		head = newNode;
	}
	return head;
}

node* removeFront(node* head,char *outVar){
	if(head==NULL){
		*outVar=-1;
		//return NULL;
	}
	else if(head->next==head){
		*outVar=freeNode(head);
		head = NULL;
	}else{
		node* newHead = head->next;
		*outVar = freeNode(head);
		head = newHead;

	}
	return head;
}

///Addition
node* Add(node* h1,node* h2){
	node *h3=NULL,*hp1=h1,*hp2=h2;
	///Assume Zeros padded already
	for(int c=0,flag=1;hp1!=h1||flag;((hp1=hp1->next),(hp2=hp2->next)) ){
		//Encountered head once, stop next time
		if(hp1==h1)flag--;
		//Add sum result
		h3 = insertFront(h3,(hp1->data+hp2->data+c)%10 );
		//Keep carry for later
		c = (hp1->data+hp2->data+c) /10;
	}
	return h3;
}

int main(){
	char add1[STRLEN],add2[STRLEN],outVar;
	int add1l=0,add2l=0,add3l,i;
	///h3 will be result from add
	node *h1=NULL,*h2=NULL,*h3=NULL;
	printf("Enter number 1\n:");
	fflush(stdin);
	scanf("%s",add1);
	printf("Enter number 2\n:");
	fflush(stdin);
	scanf("%s",add2);
	//Find length
	while(add1[add1l++]);
	while(add2[add2l++]);
	//fflush(stdout);
	///Get total length required
	add3l = (add1l>add2l?add1l:add2l) + 1;
	///Insert into lists
	///Insert blanks
	for(i=0;i<add3l-add1l;i++)
		h1 = insertFront(h1,0);
	for(i=0;i<add3l-add2l;i++)
		h2 = insertFront(h2,0);
	
	///Insert actual numbers;
	for(i=0;i<add1l-1;i++)
		h1 = insertFront(h1,add1[i]-'0');
	for(i=0;i<add2l-1;i++)
		h2 = insertFront(h2,add2[i]-'0');
	h3 = Add(h1,h2);
	for(i=0;i<add3l-1;i++){
		h3 = removeFront(h3,&outVar);
		printf("%c",outVar==-1?'?':i==0&&outVar==0?'\0':outVar+'0');
	}
	printf("\n");
	return 0;
}
