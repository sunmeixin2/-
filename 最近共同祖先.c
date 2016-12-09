#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20
typedef char DateType;
typedef struct Node{
	DateType date;
	struct Node *LChild;
	struct Node *RChild;
}BiTNode,*BiTree;
void *createBiTree()
{
	char ch;
	BiTNode *root;
	ch = getchar();
	if(ch == '#')
		return NULL;
	else
	{
		root = (BiTree)malloc(sizeof(BiTNode));
		root->date = ch;
		root->LChild = createBiTree();
		root->RChild = createBiTree();
		return root;
	}
}
//TreePath = 0
char *ComAncestor(BiTree root,char path[],int pathlen,char charDate,char p[])
{
	int i;
	if(root != NULL)
	{
		if(root->date == charDate)
		{
			for(i=0;i<pathlen;i++)
				p[i] = path[i];
			p[i] = charDate;
			i++;
			p[i] = '\0';
		}	

		else
		{
			path[pathlen] = root->date;
			ComAncestor(root->LChild,path,pathlen+1,charDate,p);
			ComAncestor(root->RChild,path,pathlen+1,charDate,p);
		}
	}
}
void comPre(char p1[],char p2[])
{

	int  i;
	int len = strlen(p1)<strlen(p2)?strlen(p1):strlen(p2);
	for(i = 0;i < len; i++)
		if(p1[i] == p2[i])
			continue;
		else
		{
			printf("%c",p1[i-1]);
			break;
		}
}
int main()
{
	BiTree root;
	char path[N];
	char ch1,ch2,p1[N],p2[N];
	root = createBiTree();
	scanf("\n%c %c",&ch1,&ch2);
	ComAncestor(root,path,0,ch1,p1);
	ComAncestor(root,path,0,ch2,p2);
	comPre(p1,p2);
	return 0;
}
