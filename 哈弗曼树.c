#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef  struct
{
    int weight;
    int parent;
    int lchild;
    int rchild;
}HTNode,*HuffmanTree;
static char N[100];
static char K[7]="ABCDEF";
typedef char **HuffmanCode;
typedef  struct
{
    int s1;
    int s2;
}MinCode;
HuffmanCode HuffmanCoding(HuffmanTree HT,HuffmanCode HC,int *w,int n);
MinCode   Select(HuffmanTree HT,int n);
HuffmanCode HuffmanCoding(HuffmanTree HT,HuffmanCode HC,int *w,int n)
{ 
    int i,s1=0,s2=0; 
    HuffmanTree p;
    char *cd;
    int f,c,start,m;
    MinCode min;
    m=2*n-1;
    HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
    for(p=HT,i=0;i<=n;i++,p++,w++)
    { 
        p->weight=*w;  
        p->parent=0; 
        p->lchild=0; 
        p->rchild=0;
    }
    for(;i<=m;i++,p++)
    { 
        p->weight=0;  
        p->parent=0; 
        p->lchild=0;
        p->rchild=0;
    }
    for(i=n+1;i<=m;i++)
    {
        min=Select(HT,i-1);
        s1=min.s1 ; 
        s2=min.s2;
        HT[s1].parent=i; 
        HT[s2].parent=i;
        HT[i].lchild=s1;
        HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
    HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
    cd=(char *)malloc(n*sizeof(char *));
    cd[n-1]='\0';
 
     
    for(i=1;i<=n;i++)
    { 
        start=n-1;
        for(c=i,f=HT[i].parent; f!=0; c=f,f=HT[f].parent)
        {
            if(HT[f].lchild==c)  
                cd[--start]='0';
            else
                cd[--start]='1';
        }
        HC[i]=(char *)malloc((n-start)*sizeof(char *));
        strcpy(HC[i],&cd[start]);   
    }
    free(cd);
    return HC;
}
 
MinCode Select(HuffmanTree HT,int n)
{  
    int min,secmin;
    int i,s1,s2;
    MinCode  code ;
    s1=1;
    s2=1;
    min = 66666;
    for(i=1;i<=n;i++)
    {
        if(HT[i].weight<min && HT[i].parent==0)
        {
            min=HT[i].weight;
            s1=i;
        }
    }
    secmin = 66666;
    for(i=1;i<=n;i++)
    {
        if((HT[i].weight<secmin) && (i!=s1) && HT[i].parent==0)
        {
            secmin=HT[i].weight; 
            s2=i;
        }
    }
    code.s1=s1;
    code.s2=s2;
    return code;
}
 
void HuffmanTranslateCoding(HuffmanTree HT, int n,char* ch)
{
    int m=2*n-1;
    int i,j=0;
    while(ch[j]!='\0')
    {
        i=m;
        while(0 != HT[i].lchild && 0 != HT[i].rchild)
        {
            if('0' == ch[j])
            {
                i=HT[i].lchild;
            }
            else
            {
                i=HT[i].rchild;
            }
            ++j;
        }
        printf("%c",K[i-1]);
    }
}
 
int main()
{
    HuffmanTree HT=NULL;
    HuffmanCode HC=NULL;
    int *w=NULL;
    int i=1,n,n2,j;
    char tran[100];
    n2 = strlen(K);
    w=(int *)malloc((n2+1)*sizeof(int *));
    w[0]=0;
    while(i<=n2){  
        scanf("%d ",&w[i]);  
    i++; 
   }
    gets(N);
    n = strlen(N);
    gets(tran);
    HC=HuffmanCoding(HT,HC,w,n2);
    for(i=1;i<=n2;i++)
    {
        printf("%c:%s\n",K[i-1],HC[i]);
    }
    for(i=0;i<=n2;i++)
    {
      for(j=0;j<n;j++)
      {
        if(K[i]==N[j]) printf("%s",HC[i+1]);
      }
    }
    printf("\n");
    HuffmanTranslateCoding(HT, n2, tran);
    return 0;
}
