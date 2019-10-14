#include<stdio.h>
#include<stdlib.h>

///Contains the tree def
typedef struct treeNode{
	struct treeNode* left;
	struct treeNode* right;
	///Contains data key
	int data;
	///Contains data
}treeNode;


///Obtain a new treeNode
///Number if null, will create a listless entry (can be used to dataload)
treeNode* getNewTreeNode(int data){
    treeNode* newNode;
    if((newNode = malloc(sizeof(treeNode)))){
        newNode->left=newNode->right=NULL;
        newNode-> data = data;
    }
    return newNode;
}


///Required to trash all data inside if any
treeNode* trashTreeNode(treeNode* someNode){
    free(someNode);
    ///Just to help
    return NULL;
}


///Delete whole tree
treeNode* upRoot(treeNode* root){
    if(root==NULL) return NULL;
    upRoot(root->left);
    upRoot(root->right);
    free(root);
    return NULL;
}

///Standard BST implementation
///Return searched element, null if not found
treeNode* treeSearch(treeNode* treenode,int searchElement){
    if(treenode==NULL){
        return NULL;
    }
    int results = searchElement - treenode->data;
    ///Was it that?
    if(!results){
        return treenode;
    }else if(results>0){
        return treeSearch(treenode->right,searchElement);
    }else{
        return treeSearch(treenode->left,searchElement);
    }
}



treeNode* insert(treeNode* root,int ele){
    if(root==NULL){
        //We found where to insert, do it
        return getNewTreeNode(ele);
    }

    int getCmp = (ele - root->data);
    if(getCmp<0){
        root->left = insert(root->left,ele);
    }else if(getCmp>0){
        root->right = insert(root->right,ele);
    }else{
        ///Equality, yikes!
        fprintf(stderr,"Element already exists!\n");
    }
    ///for anything else
    return root;
}


///Iterative approach to find min
treeNode* getMinTree(treeNode* tree){
    treeNode* temp = tree;
    for(;temp!=NULL?temp->left!=NULL:0;temp=temp->left);
    return temp;
}

treeNode* removeFromTree(treeNode* root,int data){
    ///If null, dont bother doing anything
    if(root==NULL){
        return root;
    }

    int cmpRes = data - root->data;
    ///BST descend
    if(cmpRes<0){
        root->left = removeFromTree(root->left,data);
    }else if(cmpRes>0){
        root->right = removeFromTree(root->right,data);
    }else{
        ///All cases: 
        ///0-2 children
        ///This: one or none
        if( ( root->left==NULL )|| ( root->right==NULL ) ){
            treeNode* loneChild = root->left?root->left:root->right;
            ///LIE, there was no child
            if(loneChild==NULL){
                loneChild = root;
                root = NULL;
            }else{
                ///Copy it over :O
                *root = *loneChild;
            }
            trashTreeNode(loneChild);
         }else{
            ///We have two children, oh no
            ///Get inorder successor
            treeNode* temp = getMinTree(root->right);

            ///To swap
            root->data = temp->data;
            ///Delete that thing
            root->right = removeFromTree(root->right,root->data);
        }
    } 
    ///All said, return 
    return root;
}


void printPreOrder(treeNode* root){
	if(root!=NULL){
		printf("%d ",root->data);
		printPreOrder(root->left);
		printPreOrder(root->right);
	}
}

void printInOrder(treeNode* root){
	if(root!=NULL){
		printInOrder(root->left);
		printf("%d ",root->data);
		printInOrder(root->right);
	}
}

void printPostOrder(treeNode* root){
	if(root!=NULL){
		printPostOrder(root->left);
		printPostOrder(root->right);
		printf("%d ",root->data);
	}
}

#define MENU "1.Menu\n2.Insert\n3.Delete\n4.Find\n5.PreOrder\n6.InOrder\n7.PostOrder\n0.Exit"

int main(){
	treeNode* numberRoot = NULL;int bufferVar;
	printf(MENU "\n");
	for(int choice=0;(printf("\n:"),scanf("%d",&choice)==1);){
		switch(choice){
			case 0:
				printf("...\n");
				return 0;
			case 1:
				printf(MENU "\n");
				break;
			case 2:
				printf("Enter data to insert\n:");
				scanf("%d",&bufferVar);
				numberRoot = insert(numberRoot,bufferVar);
				break;
			case 3:
				printf("Enter data to delete\n:");
				scanf("%d",&bufferVar);
				numberRoot = removeFromTree(numberRoot,bufferVar);
				break;
			case 4:
				printf("Enter data to search\n:");
				scanf("%d",&bufferVar);
				treeNode* foundElement = treeSearch(numberRoot,bufferVar);
				if(foundElement){
					printf("I:Found: %d\n",foundElement->data);
				}else{
					fprintf(stderr,"E:Not found\n");
				}
				break;
			case 5:
				printPreOrder(numberRoot);
				printf("\n");
				break;
			case 6:
				printInOrder(numberRoot);
				printf("\n");
				break;
			case 7:
				printPostOrder(numberRoot);
				printf("\n");
				break;
			default:
				printf("Invalid choice\n");
				
		}
	}
	upRoot(numberRoot);
	return 0;
}
