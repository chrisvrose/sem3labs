#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>



typedef struct treeNode{
	struct treeNode* left;
	struct treeNode* right;
	int size;
	int amountAllocated;
	///Actually a boolean for checking if Alloc or not, -1 for not, pid if
	char isAllocated;
}treeNode;


static treeNode* allocationTree = NULL;

treeNode* getNewTreeNode(int size){
	treeNode* newNode;
	if((newNode=malloc(sizeof(treeNode)) )){
		newNode->isAllocated = -1;
		newNode->amountAllocated = 0;
		newNode->size = size;
		newNode->left = NULL;
		newNode->right = NULL;
	}
	return newNode;
}

void freeTreeNode(treeNode* ptr){
	free(ptr);
}

treeNode* insertNode(treeNode* root,int pid,int sizeAlloc,int* wasAllocated){
	///Sanity case
	if(root==NULL){*wasAllocated = 0;return root;}

	
	///Test if too small, exit
	if(root->size<sizeAlloc||root->isAllocated!=-1){
		*wasAllocated=0;
		return root;
	}
	//Ended up in edge case
	if(root->left == NULL && root->right == NULL){
		//No need of dividing
		if(root->size/2 < sizeAlloc&&root->isAllocated==-1){
			//Store pls
			*wasAllocated = 1;
			root->isAllocated=pid;
			root->amountAllocated= sizeAlloc;
			return root;
		}
		//root->isAllocated=-2;
		root->left = getNewTreeNode(root->size/2);
		root->right = getNewTreeNode(root->size/2);
		

	}
	//Otherwise
	int wasAllocLeft=0,wasAllocRight=0;
	root->left = insertNode(root->left,pid,sizeAlloc,&wasAllocLeft);
	//Alloc not done
	if(!wasAllocLeft){
		root->right = insertNode(root->right,pid,sizeAlloc,&wasAllocRight);
	}


	*wasAllocated = wasAllocLeft||wasAllocRight;
	///Return self
	return root;
	
	///Dont need to subdivide anymore
	//if(root->size/2<sizeAlloc)
}



treeNode* removeNode(treeNode* root,int pid,int *wasRemoved){
	///Whatever happened here
	if(root==NULL){ *wasRemoved = 0;return root;}
	///Check if root==pid, if so, unset
	if(pid==root->isAllocated){
		*wasRemoved = 1;
		root->isAllocated  = -1;
		root->amountAllocated = 0;
		return root;
	}
	int wasRemLeft=0,wasRemRight=0;
	//Try to remove from left subtrees
	root->left = removeNode(root->left,pid,&wasRemLeft);
	//If left failed, what if in right? *gasps*
	if(!wasRemLeft){
		root->right = removeNode(root->right,pid,&wasRemRight);
	}

	*wasRemoved = wasRemLeft || wasRemRight;


	///If children exist, check if they're empty.If so, collapse them
	if(root->left&&root->right){
		if(root->left->isAllocated==-1&&root->right->isAllocated==-1){
			///ensure not grandparent
			if(!(root->left->left||root->left->right||root->right->left||root->right->right)){
				//Eradicate children
				freeTreeNode(root->left);
				freeTreeNode(root->right);
				root->left = root->right= NULL;
			}
		}
	}

	return root;
}


void printTree(treeNode* root){
	if(root==NULL)return;

	printTree(root->left);
	printf("%d\t-\t%d\t%d\n",root->size,(int)root->isAllocated,root->amountAllocated);
	printTree(root->right);
}

void printTreePost(treeNode* root){
	if(root==NULL)return;
	printTreePost(root->left);
	printTreePost(root->right);
	printf("%d\t-\t%d\t%d\n",root->size,(int)root->isAllocated,root->amountAllocated);
}


///Print Leaves
void printTreeTrunk(treeNode* root){
	if(root==NULL)return;
	printTreeTrunk(root->left);
	if(!(root->left||root->right)){
		printf("%d\t-\t%d\t%d\n",root->size,(int)root->isAllocated,root->amountAllocated);
	}
	printTreeTrunk(root->right);
}


#define MENU "1. Menu\n2. Allocate\n3. Deallocate\n4. Display Full Tree\n5. Display Memory Structure\n0.Exit" 

int main(){
	int choice,bufferVar1,bufferVar2;char bufferVarS1[32];
	allocationTree = malloc(sizeof(treeNode));
	if(!allocationTree) return 0;
	allocationTree->left = allocationTree->right = NULL;
	allocationTree->size = 256;
	allocationTree->amountAllocated = 0;
	allocationTree->isAllocated = -1;
	printf(MENU);
	for(choice=0,bufferVar1=0,bufferVar2=0;(printf("\n:"),scanf("%d",&choice));){
		switch(choice){
			case 0:
				printf("...");
				return 0;
			case 1:
				printf(MENU);
				break;
			case 2:
				printf("Allocate\n");
				int wasInserted=0;
				printf("PID\n:");
				scanf("%d",&bufferVar1);
				printf("Memory required\n:");
				scanf("%d",&bufferVar2);

				allocationTree = insertNode(allocationTree,bufferVar1,bufferVar2,&wasInserted);
				printf("Allocation %s",(wasInserted?"Successful":"Failed"));
				break;
			case 4:
				printf("Inorder\n");
				printf("Space\t\tPID\tAllocated\n");
				printTree(allocationTree);
				printf("Postorder\n");
				printf("Space\t\tPID\tAllocated\n");
				printTreePost(allocationTree);
				break;
			case 3:
				printf("Deallocate\nPID\n:");
				scanf("%d",&bufferVar1);
				int wasRemoved=0;
				allocationTree = removeNode(allocationTree,bufferVar1,&wasRemoved);
				printf("Removal %s",(wasRemoved?"Successful":"Failed"));
				break;
			case 5:
				printf("Inorder\n");
				printf("Space\t\tPID\tAllocated\n");
				printTreeTrunk(allocationTree);
				break;
			default:
				printf("Invalid choice\n");

		}
	}
	return 0;
}
