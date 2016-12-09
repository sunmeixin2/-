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
SeqQueue *Init_SeQueue(SeqQueue *q){		//置空队 
	q=malloc(sizeof(SeqQueue));
	q->front=q->rear=-1;
	return q;
}
void EnterSeqQueue(SeqQueue *q,BiTree t){		//入队 
	q->rear=(q->rear+1)%MAXSIZE;
	q->datatype[q->rear]=t;
} 
BiTree OutSeqQueue(SeqQueue *q,BiTree t){		//出队 
	q->front=(q->front+1)%MAXSIZE;
	t=q->datatype[q->front];
	return t; 
} 
int EmptySeqQueue(SeqQueue *q){			//判队空 
	if(q->front==q->rear)
		return 1;
	else
		return 0;
}
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
void LevelOrder(BiTree root){
	SeqQueue *q,*s;
	BiTree t;
	int i=0;
	q=Init_SeQueue(s);	
	t=root;
	EnterSeqQueue(q,t);
	while(!EmptySeqQueue(q)){
		t=OutSeqQueue(q,t);
		printf("%c",t->data);
		if(t->Lchild!=NULL)
			EnterSeqQueue(q,t->Lchild);
		if(t->Rchild!=NULL)
		
			EnterSeqQueue(q,t->Rchild);
	}
}
main(){
	BiTree root;
	root=create();
	LevelOrder(root);
}
