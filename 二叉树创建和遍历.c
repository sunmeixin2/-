#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
	char data;
	struct Node *Lchild;
	struct Node *Rchild;
}BiTNode,*BiTree;
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
void PreOrder(BiTree root){
	if(root){
		printf("%c",root->data);
		PreOrder(root->Lchild);
		PreOrder(root->Rchild);
	}
}
void InOrder(BiTree root){
	if(root){
		InOrder(root->Lchild);
		printf("%c",root->data);
		InOrder(root->Rchild);
	}
}
void PostOrder(BiTree root){
	if(root){
		PostOrder(root->Lchild);
		PostOrder(root->Rchild);
		printf("%c",root->data);
	}
}
main(){
	BiTree root;
	root=create();
	PreOrder(root);
	printf("\n");
	InOrder(root);
	printf("\n");
	PostOrder(root);
}

