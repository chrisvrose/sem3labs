/*

General logic:

Addition
1. Search if exists.
	True
		1. Insert into dataHead;
	False
		1. Create Tree Element


*/
#define TREE_H

#define TREE_H_STRLEN 32

typedef struct Tree{
	treeNode *root;
}Tree;


///Contains the tree def
typedef struct treeNode{
	struct treeNode* left;
	struct treeNode* right;
	//Contains data
	char name[32];
	int count;
	struct node dataHead;
}treeNode;


///Holds the number data
typedef struct node{
	///A standard notation is 10-digit number
	char number[11];
	struct node* next;
}node;
