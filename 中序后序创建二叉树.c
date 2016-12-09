#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Node{
	char data;
	struct Node *Lchild;
	struct Node *Rchild;
}BiTNode,*BiTree;
int search_num(char ch,char *array,int len){
	int i;
	for(i=0;i<len;i++){
		if(array[i]==ch){
			return i;
		}
	}
}
BiTree create(char *center,char *back,int len){
	if(len<=0)
		return NULL; 
	BiTree root;
	int index;
	root=(BiTree )malloc(sizeof(BiTNode));
	root->data=*(back+len-1);
	index=search_num(root->data,center,len);
	root->Lchild=create(center,back,index);
	root->Rchild=create(center+index+1,back+index,len-index-1);
	return root;
}

void PreOrder(BiTree root){
	if(root!=NULL){
		printf("%c",root->data);
		PreOrder(root->Lchild);
		PreOrder(root->Rchild);
	}
}
main(){
	BiTree root;
	char mc[50],lc[50];
	char ch;
	int i=0,j=0;
	scanf("%s",mc);
	scanf("%s",lc);
	root=create(mc,lc,strlen(mc));
	PreOrder(root);
}
