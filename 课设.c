#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<io.h>
#include <string.h>
#include<math.h>
#define N 256
#define M 2*N-1
#define MAXLONG 2147483647
typedef struct{
	long weight;
	int parent,Lchild,Rchild;
}HTNode,HuffmanTree[M+1];
typedef struct{
	long wt;		//频率
	unsigned char str;		//统计的字符串
}data;
typedef char *Huffmancode[N+1];

HuffmanTree ht;
data st[N] ;
int count;

void readfile(){			//从源文件中读取字符并统计频率 
	FILE *fp;
	int i,j=0,k,flag,l=0;
	unsigned char ch;
	long x;
	int fno,fsize;
	fp=fopen("1.souce","r");
	if(fp==NULL){
		printf("error open 1.souce!");
		getch();
		exit(0);
	}
	fno=fileno(fp);
	fsize=filelength(fno);
	if(fsize==0){
		printf("文件为空不能进行压缩！");
		exit(0);
	}
	printf("\n文件 %d Bytes\n",fsize);
	if(!feof(fp)){
		ch=fgetc(fp);
		st[0].str=ch;
		st[1].wt=1;	
	}
	while(!feof(fp)){
			ch=fgetc(fp);		//统计字符频率
			l++;
		flag=0;
		for(k=0;k<=j;k++){
			if(ch==st[k].str){
				st[k+1].wt++;
				flag=1;
				break; 
			}
		}
		if(!flag){
			j++;
			st[j].str=ch;
			st[j+1].wt=1;
		}
	}
	count=j;
	st[j].str='\0'; 
} 

void select(HuffmanTree ht,int pos,int *s1,int *s2){				//选双亲为0且权值最小的两节点s1,s2 

	int i,j;
	long m1,m2;			//m1存放最小权值，s1是m1在数组的下标		m2存放次小权值，s2是m2在数组的下标 
	m1=m2=MAXLONG;
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
//	if(*s1>*s2)		//使s1小于s2
//	{
//		i=*s1;
//		*s1=*s2;
//		*s2=i;
//	}

}

void CrtHuffmanTree(HuffmanTree ht){				//创建哈夫曼树  
	int i;
	int m,s1,s2;
	int n=count;
	m=2*n-1;
	for(i=1;i<=n;i++){			//初始化前N个元素为根结点 
		ht[i].weight=st[i].wt;
		ht[i].parent=0;
		ht[i].Lchild=0;
		ht[i].Rchild=0;
	}
	for(i=n+1;i<=m;i++){				//初始化后n-1个空元素 
		ht[i].weight=0;
		ht[i].parent=0;
		ht[i].Lchild=0;
		ht[i].Rchild=0;
	}
	for(i=n+1;i<=m;i++){		//从n+1个元素开始构造新结点 
		select(ht,i-1,&s1,&s2);										//在ht的前i-1项中选双亲为0且权值最小的两节点s1,s2 
		ht[i].weight=ht[s1].weight+ht[s2].weight;
		ht[i].Lchild=s1;
		ht[i].Rchild=s2;
		ht[s1].parent=i;
		ht[s2].parent=i;			
	}
	
}

void CrtHuffmancode(HuffmanTree ht,Huffmancode hc){						//	哈夫曼编码 
	//从叶子到根，逆向求各叶子结点的编码
	char *cd;
	int n=count;
	int start,i,c,p;
	cd=(char *)malloc(n*sizeof(char));					//临时编码数组
	 cd[n-1]='\0';										//从后向前逐位求编码，首先放编码结束符 
	for(i=1;i<=n;i++){							//从每个叶子结点开始，求相应的哈夫曼编码
		start=n-1;					
		c=i;											//c为当前结点 
		p=ht[i].parent;				//p为其双亲 
		while(p!=0){
			--start;
			if(ht[p].Lchild==c)			//做分支得‘0’ 
				cd[start]='0';				
			else							//右分支得‘1’
				cd[start]='1';
			c=p;
			p=ht[p].parent;			//上朔一层 
		}
		hc[i]=(char *)malloc((n-start)*sizeof(char));			//动态申请编码串空间
		strcpy(hc[i],&cd[start]);						//复制编码 
	}
	free(cd);
}
void output(Huffmancode hc){		//对原文件内容编码并将结果保存另一文件 
	FILE *fp1,*fp2;
	int fno,fsize;
	int i=0;
	unsigned char ch;
	fp1=fopen("1.souce","r");
	if(fp1==NULL){
		printf("error open 1.souce!");
		getch();
		exit(0);
	}
	fp2=fopen("2.code","wb");
	if(fp2==NULL){
		printf("error open 2.code!");
		getch();
		exit(0);
	}
	while(!feof(fp1)){
		ch=fgetc(fp1);
		for(i=0;i<count;i++){		//hc从下标1开始 	st->str从下标0开始   s从下标0开始 
			if(ch==st[i].str){
				fputs(hc[i+1],fp2);
				break;
			}
		}
	}
	fclose(fp2); 
	fclose(fp2);

} 
void compress(){			//压缩文件 
	FILE *fp1,*fp2;
	int fno,fsize1,fsize2; 
	unsigned char value;
	unsigned char s[8];
	int n,i,j,k,sum=0;
	fp1=fopen("2.code","r");
	fp2=fopen("2.txt","wb");
	if(fp1==NULL){
		printf("error open 2.code!");
		getch();
		exit(0);
	}
	if(fp2==NULL){
		printf("error open 2.txt!");
		getch();
		exit(0);
	}
	
	while(!feof(fp1)){
//		for(j=0;j<8;j++){
//			s[j]='\0';
//		}
		k=0;
		while(k!=8&&!feof(fp1)){
			s[k]=fgetc(fp1);
//			printf("%c",s[k]);
			k++;
//			printf("k:%d\n",k);
		}
		s[k]='\0';
		n=strlen(s);
//		printf("\n%d#\n",n);
		if(n==8){
			sum=0;
			for(i=0;i<n;i++){
				sum=sum+pow(2,n-i-1)*((int)s[i]-48);
			}
			value=(char)sum;
			fputc(value,fp2);
		}
		else if(n<8){
			for(i=0;i<n-1;i++){
				fputc(s[i],fp2);
			}
		}
	}
	printf("\n");
	fclose(fp1);
	fclose(fp2);
	
	fp1=fopen("1.souce","rb");
	if(fp1==NULL){
		printf("error open 1.souce!");
		getch();
		exit(0);
	}
	fno=fileno(fp1);
	fsize1=filelength(fno);
	printf("压缩前文件 :%d Bytes\n",fsize1);
	fclose(fp1);
	
	fp2=fopen("2.txt","r");
	if(fp1==NULL){
		printf("error open 2.txt!");
		getch();
		exit(0);
	}
	fno=fileno(fp2);
	fsize2=filelength(fno);
	printf("压缩后文件 :%d Bytes\n",fsize2);
	fclose(fp2); 
	printf("压缩比 %.2f\n",(fsize1-fsize2)*100/100.0/fsize1);
}
void HuffmanTranslateCoding(HuffmanTree ht)			//译码 
{
	FILE *fp1,*fp2;
	int fno ,fsize;
//	unsigned char s[256];
	unsigned char ch;
    int m=2*(count)-1;
    int i=0,j=0;
    fp1=fopen("3.decode","r");
	if(fp1==NULL){
		printf("error open 3.decode!");
		getch();
		exit(0);
	}
	fp2=fopen("3.resouce","wb");
    if(fp2==NULL){
		printf("error open 3.resouce!");
		getch();
		exit(0);
	}
	while(!feof(fp1)){
        i=m;
        while( ht[i].Lchild !=0 && ht[i].Rchild !=0)
        {
        	ch=fgetc(fp1);
            if('0' == ch)
            {
                i=ht[i].Lchild;
            }
            else
            {
                i=ht[i].Rchild;
            }
         //   ++j;
        }
//    	printf("%c",st[i-1].str);
      	fputc(st[i-1].str,fp2);
    }
    printf("\n");
    fno=fileno(fp2);
	fsize=filelength(fno);
    fclose(fp1);
    fclose(fp2);
    printf("文件解压成功！\n");
//    printf("文件 %d Bytes!\n",fsize);
}
void uncompress(){			//解压 
	FILE *fp1,*fp2;
	unsigned char ch;
	int value;
	int i,j,k=1;
	int fno,fsize;
	unsigned char s[10];
	fp1=fopen("2.txt","r");
	if(fp1==NULL){
		printf("error open 2.txt!");
		getch();
		exit(0);
	}
	fp2=fopen("3.decode","wb");
	if(fp2==NULL){
		printf("error open 3.decode!");
		getch();
		exit(0);
	}
	fno=fileno(fp1);
	fsize=filelength(fno);
//	printf("文件 %d  Bytes\n",fsize);
	while(!feof(fp1)){
//		fread(&ch,1,1,fp1);
		ch=fgetc(fp1);
//		printf("%d  %c\n",k,ch);
		k++;
		if(ch=='0'||ch =='1'){
			fputc(ch,fp2);
		}
		else{
			value=(int)ch;
			s[8]='\0';
			for(i=7;i>=0;i--){
				if(value%2==0){
					s[i]='0';
				}else{
					s[i]='1';
				}
//				s[i]=value%2;
				value=value/2;
			}
//			printf("%s\n",s);
			fputs(s,fp2);
		}

	}
	fclose(fp1);
	fclose(fp2);
}
void zifupinglv(Huffmancode hc){
	int i;
	printf("\n----------------------------------------------\n");
	for(i=0;i<count;i++){
		printf("%5c:%5d\n",st[i].str,st[i+1].wt);
	}
	printf("\n------------------------------------------------\n*****************************************\n");
	for(i=1;i<=count;i++){
		printf("%c:%s\n",st[i-1].str,hc[i]);
	//	free(hc[i]);
	}
	printf("\n****************************************\n");
}
void Menu(){
	printf("\n\n\n\n\t\t\t\t========================哈夫曼编/译码器==========================\n");
	printf("\t\t\t\t  1.显示文件的字符频率\n");
	printf("\t\t\t\t  2.压缩文件\n");
	printf("\t\t\t\t  3.解压文件\n");
	printf("\t\t\t\t  0.退出\n");
	printf("\t\t\t\t=================================================================\n");
	printf("请在0-3之间选择：");
}
main(){
	system("color 0b");	
	int choice;
	int i=0,m,j=0;
	Huffmancode hc;
//	st=(data)malloc(sizeof(data));
    Menu(); 
    readfile();
   	CrtHuffmanTree(ht); 
    CrtHuffmancode(ht,hc);
    output(hc);
    
	scanf("%d",&choice);
	do{
		
		switch(choice){
            case 1:zifupinglv(hc);
            	   system("pause");
                   system("cls");
                   Menu(); 
				   break;
            case 2:compress();
            		system("pause");
                   system("cls");
                   Menu(); 
				   break;
            case 3: uncompress();
					HuffmanTranslateCoding(ht);
            		system("pause");
                   system("cls");
                   Menu(); 
				   break;
            case 0: exit(0) ;      break;
		}
		printf("\n是否继续操作,如果想要退出系统可以选择'0'，并按回车键\n");
        printf("\n\n请选择：\n");
        scanf("%d",&choice);
	}while(choice!=0);

}
