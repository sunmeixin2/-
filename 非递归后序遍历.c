#include<stdlib.h>
#include<stdio.h>
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

//	if(s->top==MAXSIZE-1)
//		return 0;
//	else{
		s->top++;
		s->datatype[s->top]=p;
		return p;
//	} 
}
BiTree Pop_SeqStack(SeqStack *s,BiTree p){		//³öÕ» 
//	char *x;
//	if(IsEmpty_SeqStack(s))
//		return 0;
//	else{
		p=s->datatype[s->top];
//		*x=s->datatype[s->top]->data;
		s->top--;
		return p ;
//	}
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
			if((p->Rchild==NULL)||(p->Rchild==q)){		//ÅÐ¶ÏpµÄÓÒ×ÓÊ÷ÊÇ·ñÎª¿Õ£¬ÓÒ×ÓÊ÷ÊÇ·ñ¸Õ·ÃÎÊ¹ý 
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
	PostOrder(root);
}
