#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define N 30
#define M 2*N-1
typedef struct{
	int weight;
	int parent,Lchild,Rchild;
}HTNode,HuffmanTree[M+1];
typedef char *Huffmancode[N+1];
void select(HuffmanTree ht,int j,int *s1,int *s2){					//ѡ˫��Ϊ0��Ȩֵ��С�����ڵ�s1,s2 
	int i;
	int first,second;			//first������Сֵ��second�����Сֵ 
	//�ȼٶ�ǰ����Ϊ�����Сֵ 
	if(ht[1].weight<ht[2].weight){			 
		first=1;
		second=2;
	}
	else{

		first=2;
		second=1;
	}
	//�ҳ�Ȩֵ��С��������� 
	for(i=3;i<=j;i++){
		if(ht[i].parent==0){
			if(ht[i].weight<first){
		
				first=i;
				second=first;
			}
			else if(ht[i].weight<second)

				second=i;
		}
	}
	*s1=first;
	*s2=second;
}
HuffmanTree* CrtHuffmanTree(HuffmanTree ht,int *w,int n){				//������������ 
	int i;
	int m,s1,s2;
	m=2*n-1;
	for(i=1;i<=n;i++){			//��ʼ��ǰN��Ԫ��Ϊ����� 
		ht[i].weight=w[i];
		ht[i].parent=0;
		ht[i].Lchild=0;
		ht[i].Rchild=0;
	}
	for(i=n+1;i<=m;i++){			//��ʼ����n-1����Ԫ�� 
		ht[i].weight=0;
		ht[i].parent=0;
		ht[i].Lchild=0;
		ht[i].Rchild=0;
	}
	for(i=n+1;i<=m;i++){			//��n+1��Ԫ�ؿ�ʼ�����½�� 
		select(ht,i-1,&s1,&s2);										//��ht��ǰi-1����ѡ˫��Ϊ0��Ȩֵ��С�����ڵ�s1,s2 
		ht[i].weight=ht[s1].weight+ht[s2].weight;		
		ht[i].Lchild=s1;
		ht[i].Rchild=s2;
		ht[s1].parent=i;
		ht[s2].parent=i;		
	}

	return ht;
}

 Huffmancode1(HuffmanTree ht,Huffmancode hc,int n){						//	���������� 
	//��Ҷ�ӵ������������Ҷ�ӽ��ı���
	char *cd;
	int start,i,c,p;
	cd=(char *)malloc(n*sizeof(char));					//��ʱ�������� 
	cd[n-1]='\0';											//�Ӻ���ǰ��λ����룬���ȷű�������� 
	for(i=1;i<=n;i++){								//��ÿ��Ҷ�ӽ�㿪ʼ������Ӧ�Ĺ��������� 
		start=n-1;					
		c=i;										//cΪ��ǰ��� 
		p=ht[i].parent;			//pΪ��˫�� 
		while(p!=0){
			--start;
			if(ht[p].Lchild==c)				//����֧�á�0�� 
				cd[start]='0';				
			else							//�ҷ�֧�á�1�� 
				cd[start]='1';
			c=p;
			p=ht[p].parent;				//��˷һ�� 
		}
		hc[i]=(char *)malloc((n-start)*sizeof(char));			//��̬������봮�ռ� 
		strcpy(hc[i],&cd[start]);						//���Ʊ��� 
	}
	free(cd);
}
main(){
	int w[N];
	int i,n;
	char leaf[]={"ABCDEF"};
	HuffmanTree ht1,*ht;
	Huffmancode hc;
	n=strlen(leaf);
	for(i=1;i<=n;i++)
		scanf("%d",&w[i]);
	ht=CrtHuffmanTree(ht1,w,n);
	Huffmancode1(ht,hc,n);
	for(i=1;i<n+1;i++){
		printf("%s\n",hc[i]);
		free(hc[i]);
	}
}
