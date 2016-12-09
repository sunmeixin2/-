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
void LBPath(BiTree root,char path[],int pathlen){	
	int i=0;
	if(root){
		if(root->Lchild==NULL&&root->Rchild==NULL){
			printf("%c:",root->data);
			for(i=0;i<pathlen;i++){
				printf("%c",path[i]);
			}
			printf("\n");
		}
		else{
			path[pathlen]=root->data;
			LBPath(root->Lchild,path,pathlen+1);
			LBPath(root->Rchild,path,pathlen+1);
		}
	
	}
}
main(){
	BiTree root;
	char path[10];
	root=create();
	LBPath(root,path,0);
}



