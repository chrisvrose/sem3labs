#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int coeff;
	int power;
	struct node* next;
}node;

//Yank node
void freeNode(node* nodePtr){
	free(nodePtr);
}

void freeAll(node* ptr){
	if(ptr!=NULL){
		freeAll(ptr->next);
		freeNode(ptr);
	}
}

///Returns initialized node
node* getNode(int coeff,int power){
	node* Node = ( (node *)malloc( sizeof(node) ) );
	Node->coeff = coeff;
	Node->power = power;
	return Node;
}


///Returns head of modified LL
node* insertRear(node* head, node* element){
	node* tmp;
	//If element given is invalid, safely exit
	if(element==NULL){
		return head;
	}
	for(tmp=head;tmp!=NULL?tmp->next!=NULL:0;tmp=tmp->next);
	//If empty
	if(tmp==NULL){
		tmp=element;
		//New head
		return tmp;
	}else{
		tmp->next=element;
		return head;
	}
}

void displayLList(node* head){
	if(head==NULL){
		printf("0");
	}else{
		for(node *tmp = head; tmp!=NULL;tmp=tmp->next){
			//printf(": (%d,%d)\n",tmp->coeff,tmp->power);
			printf("%dx^%d%c",tmp->coeff,tmp->power,tmp->next==NULL?' ':'+');
		}
	}
	printf("\n");
}


///Perform multiplication, return new head
node* multiplyPoly(node* p1,node *p2,node* res){
	int calcCoeff,calcPower;
	for(node *pp1=p1;pp1!=NULL;pp1=pp1->next){
		for(node *pp2=p2;pp2!=NULL;pp2=pp2->next){
			//Calculate element results
			calcCoeff=pp1->coeff * pp2->coeff;
			calcPower=pp1->power + pp2->power;
			//Check if product result alreadt exists, if flagIfExists, create new node
			int flagIfExists = 0;
			node* rp;
			if(res!=NULL){
				for(rp=res;rp!=NULL;rp=rp->next){
					if(rp->power==calcPower){
						flagIfExists=1;
						rp->coeff+=calcCoeff;
						break;
					}
				}
			}
			//If flagifexists, set rp. Else, create at end with required values
			if(!flagIfExists){
				res = insertRear( res,getNode(calcCoeff,calcPower) );
			}
		}
	}
	return res;
}



int main(){
	node *p1,*p2,*res;p1=p2=res=NULL;int pl1=0,pl2=0, bufferCoeff,bufferPower;
	//Input polynomial one
	printf("Enter number of elements in polynomial 1\n:");
	scanf("%d",&pl1);
	for(int i=0;i<pl1;i++){
		printf("Enter coefficient, and power\n:");
		scanf("%d %d",&bufferCoeff,&bufferPower);
		p1 = insertRear(p1,getNode(bufferCoeff,bufferPower));
	}
	//Input polynomial two
	printf("Enter number of elements in polynomial 2\n:");
	scanf("%d",&pl2);
	for(int i=0;i<pl2;i++){
		printf("Enter coefficient, and power\n:");
		scanf("%d %d",&bufferCoeff,&bufferPower);
		p2 = insertRear(p2,getNode(bufferCoeff,bufferPower));
	}
	///Multiply
	res = multiplyPoly(p1,p2,res);

	displayLList(p1);
	displayLList(p2);
	displayLList(res);

	///Recursively free all the linked Lists
	freeAll(p1);
	freeAll(p2);
	freeAll(res);

	return 0;
}
