#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
typedef struct Node{
	char data;
	struct Node *Lchild;
	struct Node *Rchild;
}BiTNode,*BiTree;
typedef struct {
	BiTree datatype[MAXSIZE];
	int front,rear;
}SeqQueue;
BiTree create(){
	char ch;
	BiTree root;
	ch=getchar(); 
	if(ch=='#'){
		root=NULL;
	}
	else{
		root=(BiTree )malloc(sizeof(BiTNode));
		root->data=ch;
		root->Lchild=create();
		root->Rchild=create();
	}
	return root;
} 
void LevelOrder(BiTree root,int n){
	int l;
	if(root){
		printf("(%c,%d)",root->data,n);
		LevelOrder(root->Lchild,n+1);
		LevelOrder(root->Rchild,n+1);
	}
	
}
main(){
	BiTree root;
	root=create();
	LevelOrder(root,1);
}
