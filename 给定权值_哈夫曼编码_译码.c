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

void select(HuffmanTree ht,int pos,int *s1,int *s2){					//ѡ˫��Ϊ0��Ȩֵ��С�����ڵ�s1,s2 

	int i,j,m1,m2;			//m1�����СȨֵ��s1��m1��������±�		m2��Ŵ�СȨֵ��s2��m2��������±� 
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
//	if(*s1>*s2)			//ʹs1С��s2 
//	{
//		i=*s1;
//		*s1=*s2;
//		*s2=i;
//	}

}

void CrtHuffmanTree(HuffmanTree ht,int *w,int n){				//������������ 
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
	
}
typedef char* HuffmanCode[N+1];
void CrtHuffmancode(HuffmanTree ht,Huffmancode hc,int n){						//	���������� 
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
