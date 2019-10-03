#ifndef TREE_H
#include<tree.h>
#endif

#ifndef _STRING_H
#include<string.h>
#endif

#define PMNULL ((void*)0)

treeNode* treeSearch(Tree* t,char* searchElement){
    /* Check against errors */
    if(t==PMNULL){
        return PMNULL;
    }
    else{
        return treeSearch(t->root,searchElement);
    }
}

treeNode* treeSearch(treeNode* treenode,char* searchElement){
    if(treenode==PMNULL){
        return PMNULL;
    }
    int results = strcmp(treenode->name,searchElement);
    //
    if(!results){
        return treenode;
    }else if(results>0){
        return treeSearch(treenode->left,searchElement);
    }else{
        return treeSearch(treenode->right,searchElement);
    }
}