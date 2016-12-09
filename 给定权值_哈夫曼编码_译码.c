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
void select(HuffmanTree ht,int j,int *s1,int *s2){					//选双亲为0且权值最小的两节点s1,s2 
	int i;
	int first,second;			//first保存最小值，second保存次小值 
	//先假定前两项为最大最小值 
	if(ht[1].weight<ht[2].weight){			 
		first=1;
		second=2;
	}
	else{

		first=2;
		second=1;
	}
	//找出权值最小的两个结点 
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
HuffmanTree* CrtHuffmanTree(HuffmanTree ht,int *w,int n){				//创建哈夫曼树 
	int i;
	int m,s1,s2;
	m=2*n-1;
	for(i=1;i<=n;i++){			//初始化前N个元素为根结点 
		ht[i].weight=w[i];
		ht[i].parent=0;
		ht[i].Lchild=0;
		ht[i].Rchild=0;
	}
	for(i=n+1;i<=m;i++){			//初始化后n-1个空元素 
		ht[i].weight=0;
		ht[i].parent=0;
		ht[i].Lchild=0;
		ht[i].Rchild=0;
	}
	for(i=n+1;i<=m;i++){			//从n+1个元素开始构造新结点 
		select(ht,i-1,&s1,&s2);										//在ht的前i-1项中选双亲为0且权值最小的两节点s1,s2 
		ht[i].weight=ht[s1].weight+ht[s2].weight;		
		ht[i].Lchild=s1;
		ht[i].Rchild=s2;
		ht[s1].parent=i;
		ht[s2].parent=i;		
	}

	return ht;
}

 Huffmancode1(HuffmanTree ht,Huffmancode hc,int n){						//	哈夫曼编码 
	//从叶子到根，逆向求各叶子结点的编码
	char *cd;
	int start,i,c,p;
	cd=(char *)malloc(n*sizeof(char));					//临时编码数组 
	cd[n-1]='\0';											//从后向前逐位求编码，首先放编码结束符 
	for(i=1;i<=n;i++){								//从每个叶子结点开始，求相应的哈夫曼编码 
		start=n-1;					
		c=i;										//c为当前结点 
		p=ht[i].parent;			//p为其双亲 
		while(p!=0){
			--start;
			if(ht[p].Lchild==c)				//做分支得‘0’ 
				cd[start]='0';				
			else							//右分支得‘1’ 
				cd[start]='1';
			c=p;
			p=ht[p].parent;				//上朔一层 
		}
		hc[i]=(char *)malloc((n-start)*sizeof(char));			//动态申请编码串空间 
		strcpy(hc[i],&cd[start]);						//复制编码 
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
