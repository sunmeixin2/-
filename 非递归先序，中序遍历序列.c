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
	int top;
}SeqStack;
int IsEmpty_SeqStack(SeqStack *s){		//ÅÐ¿ÕÕ» 
	if(s->top== -1)
		return 1;
	else
		return 0;
}
SeqStack *Init_SeqStack(SeqStack *s){		//ÖÃ¿ÕÕ» 
	s=malloc(sizeof(SeqStack));
	s->top= -1;
	return s;
}

BiTree Push_SeqStack(SeqStack *s,BiTree p){		//ÈëÕ» 

		s->top++;
		s->datatype[s->top]=p;
		return p;

}
BiTree Pop_SeqStack(SeqStack *s,BiTree p){		//³öÕ» 

		p=s->datatype[s->top];
		s->top--;
		return p ;

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
void PreOrder(BiTree root){		//ÏÈÐò·ÇµÝ¹é±éÀú 
	SeqStack *t,*s;
	BiTree p;
	s=Init_SeqStack(t);	//ÖÃ¿ÕÕ» 
	p=root;
	while(p!=NULL||!IsEmpty_SeqStack(s)){
		while(p!=NULL){
			printf("%c",p->data);
			Push_SeqStack(s,p);
			p=p->Lchild;
		}
		if(!IsEmpty_SeqStack(s)){
			p=Pop_SeqStack(s,p);
			p=p->Rchild;
		}
	}
	
}
void InOrder(BiTree root){			//ÖÐÐò·ÇµÝ¹é 
	SeqStack *s,*t;
	BiTree p;
	p=root;
	s=Init_SeqStack(t);
	while(p!=NULL||!IsEmpty_SeqStack(s)){
		while(p!=NULL){
			Push_SeqStack(s,p);
			p=p->Lchild;
		}
		if(!IsEmpty_SeqStack(s)){
			p=Pop_SeqStack(s,p);
			printf("%c",p->data);
			p=p->Rchild;
		}
	}
} 
BiTree Top(SeqStack *s,BiTree p){
	p=s->datatype[s->top];
	return p;
} 
void PostOrder(BiTree root){			//ºóÐò·ÇµÝ¹é 
	BiTree q,p;
	SeqStack *s,*t;
	s=Init_SeqStack(t);
	p=root;
	q=NULL;
	while(p!=NULL||!IsEmpty_SeqStack(s)){
		while(p!=NULL){
			Push_SeqStack(s,p);
			p=p->Lchild;
		}
		if(!IsEmpty_SeqStack(s)){
			p=Top(s,p);
			if((p->Rchild==NULL)||(p->Rchild==q)){
				Pop_SeqStack(s,p);
				printf("%c",p->data);
				q=p;
				p=NULL;
			}
			else
				p=p->Rchild;
		}
	}
}
main(){
	BiTree root;
	root=create();
	PreOrder(root);
//	printf("\n");
//	InOrder(root);
//	PostOrder(root);
}
