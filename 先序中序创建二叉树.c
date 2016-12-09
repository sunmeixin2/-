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
		if(array[i]==ch)
			return i;
	}
}
BiTree create(char *front,char *center,int len){
	if(len<=0)
		return NULL; 
	BiTree root;
	int index;
	root=(BiTree )malloc(sizeof(BiTNode));
	root->data=*front;
	index=search_num(*front,center,len);

	root->Lchild=create(front+1,center,index);
	root->Rchild=create(front+index+1,center+index+1,len-index-1);
	return root;
	 
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
	char fc[50],mc[50];
	char ch;
	int i=0,j=0;
	scanf("%s",fc);
	scanf("%s",mc);
	root=create(fc,mc,strlen(mc));
	PostOrder(root);

}
