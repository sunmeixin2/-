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
int x=0;
void LevelLeaf(BiTree root,int m){
	if(root!=NULL&&m>0){
		if(root->Lchild==NULL&&root->Rchild==NULL){
			x++;
		}
		LevelLeaf(root->Lchild,m-1);
		LevelLeaf(root->Rchild,m-1);
	}
}
main(){
	BiTree root;
	int n;
	root=create();
	scanf("%d",&n);
	LevelLeaf(root,n);
	printf("%d",x);
}
