//Doubly linked list
#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	struct node *prev;
	struct node *next;
	int data;
	int row;
	int col;
}node;

node* getNode(int data,int row,int col){
	node* newNode;
	if((newNode = malloc(sizeof(node)))){
		newNode->data = data;
		newNode->row = row;
		newNode->col = col;
	}
	return newNode;
}

void freeAll(node *head){
	if(head!=NULL){
		freeAll(head->next);
		free(head);
	}
}

node* insertEnd(node *head,int data,int row,int col,int *status){
	node *newNode;
	if(newNode = getNode(data,row,col)){
		if(status!=NULL) *status=0;
		///Successful in getting data
		///No elements
		if(head==NULL){
			return newNode;
		///Atleast one element
		}else{
			node *tmp;
			for(tmp = head ; tmp->next!=NULL;tmp=tmp->next);
			tmp->next = newNode;
			newNode->prev = newNode;
			return head;
		}
	}else{
		if(status!=NULL) *status=1;
		///Could not get, abort
		return head;
	}
}

void sparseDisplay(node* head){
	printf("r\tc\td\n");
	for(node* tmp = head; tmp!=NULL;tmp=tmp->next){
		printf("%d\t%d\t%d\n",tmp->row,tmp->col,tmp->data);
	}
	printf("\n");
}

void matrixDisplay(node* head,int row,int col){
	node *tmp = head;
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			if(tmp==NULL?0:(tmp->row==i&&tmp->col==j)){
				printf("%d\t",tmp->data);
				tmp = tmp->next;
			}else{
				printf("0\t");
			}
		}
		printf("\n");
	}
}

int main(){
	node *head = NULL;
	int r,c,buffer;
	printf("Enter the size of the matrix\n:");
	scanf("%d %d",&r,&c);
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			if(scanf("%d",&buffer)==1){
				if(buffer!=0){
					head = insertEnd(head,buffer,i,j,NULL);
				}
			}
		}
	}
	///Done with matrix input
	///Do the outputs
	sparseDisplay(head);
	matrixDisplay(head,r,c);
	freeAll(head);
	return 0;
}



