#define TREE_H

#define TREE_H_STRLEN 32

///Contains the tree def
typedef struct treeNode{
	treeNode* left;
	treeNode* right;
	//Contains data
	char name[32];
	int count;
	node* dataHead;
}treeNode;


///Holds the number data
typedef struct node{
	///A standard notation is 10-digit number
	char number[11];
	node* next;
}node;
