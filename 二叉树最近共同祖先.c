#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 100
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
void LastParent(BiTree root,char c){
		char a[100];
		int i=0;
		if(root){
			while(root->data!=c)
			{
				a[i]=root->data;
				i++;
				root=root->Lchild;
			}
	}
	return a;
}
main(){
	BiTree root;
	char c1,c2;
	char a[100],b[100];
	root=create();
	getchar();
	scanf("%c %c",&c1,&c2);
	a=LastParent(root,c1);
	b=LastParent(root,c2);
		for(i=0;i<100;i++){
		for(j=0;j<strlen(b);j++){
			if(a[i]==b[j]){
				printf("%c",b[j]);
				break;
			}
		}
	}
}

