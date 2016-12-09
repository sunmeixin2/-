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
int PostOrderleaf(BiTree root){			//输出叶子结点个数 
	int nl,nr;
	if(root==NULL)
		return 0;
	if(root->Lchild==NULL&&root->Rchild==NULL)
		return 1;
	nl=PostOrderleaf(root->Lchild);
	nr=PostOrderleaf(root->Rchild);
	return (nl+nr);
}
int n1=0;
void InOrder_one(BiTree root){		//度为一的结点个数
	
	if(root){
		if(root->Lchild==NULL && root->Rchild!=NULL)
			n1++;
		else if(root->Lchild!=NULL && root->Rchild==NULL)
			n1++;
		InOrder_one(root->Lchild);
		InOrder_one(root->Rchild);
	}
}
int n2=0;
void InOrder_two(BiTree root){			//输出二度结点个数
	 if(root){
	 	if(root->Lchild!=NULL && root->Rchild!=NULL)
	 		n2++;
	 	InOrder_two(root->Lchild);
	 	InOrder_two(root->Rchild);
	 }
} 
void InOrderleaf(BiTree root){		//输出叶子结点  
	if(root){
		InOrderleaf(root->Lchild);
		if(root->Lchild==NULL&&root->Rchild==NULL){
			printf("%c",root->data);
		}
		InOrderleaf(root->Rchild);
	}
}
main()
{
	BiTree root;
	int n;
	root=create();
	n=PostOrderleaf(root);
	InOrder_one(root);
	InOrder_two(root);
	printf("%d %d %d\n",n,n1,n2);
	InOrderleaf(root);
}
