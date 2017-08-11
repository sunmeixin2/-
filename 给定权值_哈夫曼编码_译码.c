#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define N 20
#define M 2*N-1
#define MAXINT 32767
typedef struct{
	int weight;
	int parent,Lchild,Rchild;
}HTNode,HuffmanTree[M+1];
typedef char *Huffmancode[N+1];

HuffmanTree ht;

void select(HuffmanTree ht,int pos,int *s1,int *s2){					//选双亲为0且权值最小的两节点s1,s2 

	int i,j,m1,m2;			//m1存放最小权值，s1是m1在数组的下标		m2存放次小权值，s2是m2在数组的下标 
	m1=m2=MAXINT;
	for(j=1;j<=pos;j++){
	 	if(ht[j].weight<m1 && ht[j].parent==0)
		 {
	 		m2=m1;
	 		*s2=*s1;
	 		*s1=j;
	 		m1=ht[j].weight;
	 	}
		else if(ht[j].weight<m2 && ht[j].parent==0)
		 {
	 			m2=ht[j].weight;
	 			*s2=j;
	 		
	 	}
	}
//	if(*s1>*s2)			//使s1小于s2 
//	{
//		i=*s1;
//		*s1=*s2;
//		*s2=i;
//	}

}

void CrtHuffmanTree(HuffmanTree ht,int *w,int n){				//创建哈夫曼树 
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
	
}
typedef char* HuffmanCode[N+1];
void CrtHuffmancode(HuffmanTree ht,Huffmancode hc,int n){						//	哈夫曼编码 
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
void HuffmanTranslateCoding(HuffmanTree HT, int n,char* ch,char K[])
{
    int m=2*n-1;
    int i,j=0;
    while(ch[j]!='\0')
    {
        i=m;
        while(0 != HT[i].Lchild && 0 != HT[i].Rchild)
        {
            if('0' == ch[j])
            {
                i=HT[i].Lchild;
            }
            else
            {
                i=HT[i].Rchild;
            }
            ++j;
        }
        printf("%c",K[i-1]);
    }
}
main(){
	int w[N];
	int i,n,m,j=0;
	char str[10],tran[100];
	char leaf[]={"ABCDEF"};
	Huffmancode hc;
	n=strlen(leaf);
	for(i=1;i<=n;i++)
		scanf("%d",&w[i]);
	CrtHuffmanTree(ht,w,n);
	getchar();
	gets(str);
	gets(tran);
	CrtHuffmancode(ht,hc,n);
	for(i=1;i<=n;i++){
		printf("%c:%s\n",leaf[i-1],hc[i]);
		free(hc[i]);
	}
	m=strlen(str);
	while(j<m){
		
		for(i=1;i<=n;i++){
			if(str[j]==leaf[i-1]){
				printf("%s",hc[i]);
			}
		}
		j++;
	}
	printf("\n");
    HuffmanTranslateCoding(ht, n,tran,leaf);

}
