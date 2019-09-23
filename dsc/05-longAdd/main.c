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

node* removeRear(node* head,char *outVar){
	//char outVar;
	if(head==NULL){
		return -1;
	}else if(head->next == head){
		*outVar = (char)freeNode(head);
		return NULL;
		//return(freeNode(head));
	}else{
		node *lastBefore;
		///Get secondlast element
		for(lastBefore=head;lastBefore->next->next!=head;lastBefore= lastBefore->next);
		*outVar = (char)freeNode(lastBefore->next);
		lastBefore->next = head;
		return head;
	}
}

void displayList(node* ptr){
	for(node* tmp=ptr;tmp!=ptr;tmp=tmp->next){
		printf("%c",tmp->data+'0');
	}
	printf("\n");
}


///Addition
node* Add(node* h1,node* h2){
	node *h3,*hp1=h1,*hp2=h2;
	///Assume Zeros padded already
	for(int c=0;hp1->next!=NULL || hp2->next!=NULL;((hp1=hp1->next),(hp2=hp2->next)) ){
		//Add sum result
		insertFront(h3,(hp1->data+hp2->data+c)%10 );
		//Keep carry for later
		c = hp1->data+hp2->data /10;
	}
	return h3;
}

int main(){
	char add1[STRLEN],add2[STRLEN],result[STRLEN];
	int add1l=0,add2l=0,add3l,i;
	///h3 will be result from add
	node *h1=NULL,*h2=NULL,*h3=NULL;
	printf("Enter number 1\n:");
	scanf(" %s",add1);
	printf("Enter number 2\n:");
	scanf(" %s",add2);
	//Find length
	while(add1[add1l++]);
	while(add2[add2l++]);
	
	///Get total length required
	add3l = add1l>add2l?add1l:add2l + 1;
	
	///Insert into lists
	///Insert blanks
	for(i=0;i<add3l-add1l;i++)
		h1 = insertFront(h1,0);
	for(i=0;i<add3l-add2l;i++)
		h2 = insertFront(h2,0);
	
	///Insert actual numbers;
	for(i=0;i<add1l;i++)
		h1 = insertFront(h1,add1[i]-'0');
	for(i=0;i<add2l;i++)
		h2 = insertFront(h2,add2[i]-'0');
	//h3 = Add(h1,h2);
	displayList(h1);
	displayList(h2);
	//displayList(h3);

	/**/
	return 0;
}
