#include <stdio.h>
#include <stdlib.h>
#define max 101

typedef int ElementType;
typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType element;
    Tree  left;
    Tree  right;
};

int read();//read partial in-order, pre-order, post-order traversal
int buildtree(Tree T,int in_l,int in_r,int pre_l,int pre_r,int post_l,int post_r);//build complete tree by reading broken tree's traversals
void dfs_output(Tree T,int y);//output traversals in in-order, pre- order or post-order 
void bfs_output(Tree T);//output traversals in level-order
void enQueue(Tree T);//treenode entry queue
void deQueue();//treenode quit queue

int in[max],pre[max],post[max],f[max];//respectively store in-order, pre-order, post-order traversal and numbers that have appeared
int rear,front;//rear and front of queue
Tree que[max];//queue
int flag,missing_one;
int main()
{
	int n;
	scanf("%d", &n);
	int i,cnt = 0;
	Tree root=NULL,T=(Tree)malloc(sizeof(struct TreeNode));
	root=T;//initialize Tree
	for (i=1;i<=n;i++) {in[i]=read(); f[in[i]]++;}//read partial in-order traversal
	for (i=1;i<=n;i++) {pre[i]=read(); f[pre[i]]++;}//read partial pre-order traversal
	for (i=1;i<=n;i++) {post[i]=read(); f[post[i]]++;}//read partial post-order traversal
	for (i=1;i<=n;i++) {if(!f[i]) cnt++, missing_one=i;}//check whether there are more than 1 digits missing
	if (cnt>1||!buildtree(T,1,n,1,n,1,n)) printf("Impossible\n");
	else {
		flag=0; dfs_output(root,1); printf("\n");//output complete in-order traversal
		flag=0; dfs_output(root,2); printf("\n");//output complete pre-order traversal
		flag=0; dfs_output(root,3); printf("\n");//output complete post-order traversal
		flag=0; bfs_output(root); printf("\n");//output complete level-order traversal
	}
	return 0;
}

int read() //swich char into int
{
	char s[4];
	scanf("%s",s);
	if (s[0]=='-') return 0;
	int num=0;
	int i;
	for (i=0;s[i];i++) num=num*10+s[i]-'0';
	return num;
}

int buildtree(Tree T,int in_l,int in_r,int pre_l,int pre_r,int post_l,int post_r) 
{
	T->element=0;//initialize T node
	T->left=(Tree)malloc(sizeof(struct TreeNode));
	T->right=(Tree)malloc(sizeof(struct TreeNode));
	if (in_l > in_r) return 1; 
	int i;
	for (i = in_l; i <=in_r ; i++)
	{
		if (in[i]&&pre[pre_l]&&in[i]!=pre[pre_l]) continue;
		if (in[i]&&post[post_r]&&in[i]!=post[post_r]) continue;
		if (pre[pre_l]&&post[post_r]&&pre[pre_l]!=post[post_r]) continue;//find the root of current subtree
		T->element= in[i]|pre[pre_l]|post[post_r]?in[i]|pre[pre_l]|post[post_r]:missing_one;
		//if in[i]|pre[pre_l]|post[post_r]=0,then T->element=missing_one
		if (!buildtree(T->left,in_l,i-1,pre_l+1,pre_l+i-in_l,post_l,post_l+i-in_l- 1)) continue;//build left subtree
		if (!buildtree(T->right,i+1,in_r,pre_l+1+i-in_l,pre_r,post_l+i-in_l,post_r-1)) continue;//build right subtree
 
		return 1;
	}
	return 0;
}
 
void dfs_output(Tree T,int y) 
{
	if (y==2) {printf("%s%d",flag ? " " :"",T->element);flag=1;}//in-order
	if (T->left->element) dfs_output(T->left, y);
	if (y==1) {printf("%s%d",flag ? " " :"",T->element);flag=1;}//pre-order
	if (T->right->element) dfs_output(T->right, y);
	if (y==3) {printf("%s%d",flag ? " " :"",T->element);flag=1;}//post-order
}
void bfs_output(Tree T) //level-order
{
	enQueue(T);
	while (front!=rear) {
		T = que[front]; 
		deQueue();
		printf("%s%d", flag ? " " : "", T->element); flag = 1;
		if (T->left->element) enQueue(T->left);
		if (T->right->element) enQueue(T->right);
	}
}
                          
void enQueue(Tree T)
{
    que[rear]=T;
    rear++;
}
void deQueue()
{
    front++;
}
