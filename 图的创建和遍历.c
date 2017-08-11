#define MAXVEX 20
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct ArcNode{
	int adj;
	int weight;
	struct ArcNode *nextarc;
}ArcNode;
typedef struct VertexNode{
	char data;
	ArcNode *firstarc;
}VertexNode;
typedef struct{
	VertexNode vertex[MAXVEX];
	int vernum;		//顶点数 
	int arcnum;		//弧数 
}ALGraph;
int locate(ALGraph g,char u){
	int i;
	for(i=0;i<g.vernum;i++)
		if(g.vertex[i].data==u)
			break;
	 if(i<g.vernum)
			return (i+1);
	else
			return 0;
	
}
void creatDG(ALGraph g){
	int i,j,k;
	char v1,v2;
	ArcNode *s,*p;
	scanf("%d%d",&g.vernum,&g.arcnum);
//	flushall();
	printf("please input the vertex:");
	for(i=1;i<g.vernum;i++){
		scanf("%c",&g.vertex[i].data);
		g.vertex[i].firstarc=NULL;
	}
	getchar();
	//创建边 
	for(k=1;k<=g.arcnum;k++){
//		flushall();
		printf("please input v1,v2:");
		scanf("%c%c",&v1,&v2);
		getchar();
		i=locate(g,v1);
		j=locate(g,v2);
		s=(ArcNode *)malloc(sizeof(ArcNode));
		s->adj=j;
		s->nextarc=NULL;
			//插入结点s
		for(k=1;k<=g.arcnum;k++){
			p=g.vertex[i].firstarc;
			if(p==NULL){
				g.vertex[i].firstarc=s;
			}else if(p->adj>j){
				s->nextarc=p;
				g.vertex[i].firstarc=s;
			}else{
				while(p->nextarc&&p->nextarc->adj<j)
					p=p->nextarc;
				s->nextarc=p->nextarc;
				p->nextarc=s;
			}
		} 
	}

} 
//打印矩阵
void outputDG(ALGraph g){
	int i;
	ArcNode *p;
	for(i=1;i<=g.vernum;i++){
		printf("\n%d%c\t",i,g.vertex[i].data);
		p=g.vertex[i].firstarc;
		while(p){
			printf("%d\t",p->adj);
			p=p->nextarc;
		}
	}
	printf("\n");
} 
main(){
	ALGraph *g;
	creatDG(*g);
	outputDG(*g);
	
} 




