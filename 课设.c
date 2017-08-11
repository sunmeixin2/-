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
	long wt;		//Ƶ��
	unsigned char str;		//ͳ�Ƶ��ַ���
}data;
typedef char *Huffmancode[N+1];

HuffmanTree ht;
data st[N] ;
int count;

void readfile(){			//��Դ�ļ��ж�ȡ�ַ���ͳ��Ƶ�� 
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
		printf("�ļ�Ϊ�ղ��ܽ���ѹ����");
		exit(0);
	}
	printf("\n�ļ� %d Bytes\n",fsize);
	if(!feof(fp)){
		ch=fgetc(fp);
		st[0].str=ch;
		st[1].wt=1;	
	}
	while(!feof(fp)){
			ch=fgetc(fp);		//ͳ���ַ�Ƶ��
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

void select(HuffmanTree ht,int pos,int *s1,int *s2){				//ѡ˫��Ϊ0��Ȩֵ��С�����ڵ�s1,s2 

	int i,j;
	long m1,m2;			//m1�����СȨֵ��s1��m1��������±�		m2��Ŵ�СȨֵ��s2��m2��������±� 
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
//	if(*s1>*s2)		//ʹs1С��s2
//	{
//		i=*s1;
//		*s1=*s2;
//		*s2=i;
//	}

}

void CrtHuffmanTree(HuffmanTree ht){				//������������  
	int i;
	int m,s1,s2;
	int n=count;
	m=2*n-1;
	for(i=1;i<=n;i++){			//��ʼ��ǰN��Ԫ��Ϊ����� 
		ht[i].weight=st[i].wt;
		ht[i].parent=0;
		ht[i].Lchild=0;
		ht[i].Rchild=0;
	}
	for(i=n+1;i<=m;i++){				//��ʼ����n-1����Ԫ�� 
		ht[i].weight=0;
		ht[i].parent=0;
		ht[i].Lchild=0;
		ht[i].Rchild=0;
	}
	for(i=n+1;i<=m;i++){		//��n+1��Ԫ�ؿ�ʼ�����½�� 
		select(ht,i-1,&s1,&s2);										//��ht��ǰi-1����ѡ˫��Ϊ0��Ȩֵ��С�����ڵ�s1,s2 
		ht[i].weight=ht[s1].weight+ht[s2].weight;
		ht[i].Lchild=s1;
		ht[i].Rchild=s2;
		ht[s1].parent=i;
		ht[s2].parent=i;			
	}
	
}

void CrtHuffmancode(HuffmanTree ht,Huffmancode hc){						//	���������� 
	//��Ҷ�ӵ������������Ҷ�ӽ��ı���
	char *cd;
	int n=count;
	int start,i,c,p;
	cd=(char *)malloc(n*sizeof(char));					//��ʱ��������
	 cd[n-1]='\0';										//�Ӻ���ǰ��λ����룬���ȷű�������� 
	for(i=1;i<=n;i++){							//��ÿ��Ҷ�ӽ�㿪ʼ������Ӧ�Ĺ���������
		start=n-1;					
		c=i;											//cΪ��ǰ��� 
		p=ht[i].parent;				//pΪ��˫�� 
		while(p!=0){
			--start;
			if(ht[p].Lchild==c)			//����֧�á�0�� 
				cd[start]='0';				
			else							//�ҷ�֧�á�1��
				cd[start]='1';
			c=p;
			p=ht[p].parent;			//��˷һ�� 
		}
		hc[i]=(char *)malloc((n-start)*sizeof(char));			//��̬������봮�ռ�
		strcpy(hc[i],&cd[start]);						//���Ʊ��� 
	}
	free(cd);
}
void output(Huffmancode hc){		//��ԭ�ļ����ݱ��벢�����������һ�ļ� 
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
		for(i=0;i<count;i++){		//hc���±�1��ʼ 	st->str���±�0��ʼ   s���±�0��ʼ 
			if(ch==st[i].str){
				fputs(hc[i+1],fp2);
				break;
			}
		}
	}
	fclose(fp2); 
	fclose(fp2);

} 
void compress(){			//ѹ���ļ� 
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
	printf("ѹ��ǰ�ļ� :%d Bytes\n",fsize1);
	fclose(fp1);
	
	fp2=fopen("2.txt","r");
	if(fp1==NULL){
		printf("error open 2.txt!");
		getch();
		exit(0);
	}
	fno=fileno(fp2);
	fsize2=filelength(fno);
	printf("ѹ�����ļ� :%d Bytes\n",fsize2);
	fclose(fp2); 
	printf("ѹ���� %.2f\n",(fsize1-fsize2)*100/100.0/fsize1);
}
void HuffmanTranslateCoding(HuffmanTree ht)			//���� 
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
    printf("�ļ���ѹ�ɹ���\n");
//    printf("�ļ� %d Bytes!\n",fsize);
}
void uncompress(){			//��ѹ 
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
//	printf("�ļ� %d  Bytes\n",fsize);
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
	printf("\n\n\n\n\t\t\t\t========================��������/������==========================\n");
	printf("\t\t\t\t  1.��ʾ�ļ����ַ�Ƶ��\n");
	printf("\t\t\t\t  2.ѹ���ļ�\n");
	printf("\t\t\t\t  3.��ѹ�ļ�\n");
	printf("\t\t\t\t  0.�˳�\n");
	printf("\t\t\t\t=================================================================\n");
	printf("����0-3֮��ѡ��");
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
		printf("\n�Ƿ��������,�����Ҫ�˳�ϵͳ����ѡ��'0'�������س���\n");
        printf("\n\n��ѡ��\n");
        scanf("%d",&choice);
	}while(choice!=0);

}
