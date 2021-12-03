#include<stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType element;
    Tree  left;
    Tree  right;
    Tree  next;
};
void buildtree(int index[],int postorder[],int head,int foot,Tree T);
void output(Tree T);
void push(Tree T,Tree S);
Tree pop(Tree S);
int main()
{
    int n,i,j;
    scanf("%d",&n);
    int inorder[n],postorder[n],index[n];
    for(i=0;i<=n-1;i++)
        scanf("%d",&inorder[i]);
    for(i=0;i<=n-1;i++)
        scanf("%d",&postorder[i]);
    for(i=0;i<=n-1;i++)
    {
        for(j=0;j<=n-1;j++)
        if(inorder[i]==postorder[j]) 
        {
            index[i]=j;
            break;
        }
    }
    Tree root=NULL,T=(Tree)malloc(sizeof(struct TreeNode));
    root=T;
    buildtree(index,postorder,0,n-1,T);
    output(root);
    return 0;
}
void output(Tree T)
{
	Tree stack1=(Tree)malloc(sizeof(struct TreeNode));
	stack1->next=NULL;
	Tree stack2=(Tree)malloc(sizeof(struct TreeNode));
	stack2->next=NULL;
    push(T,stack1);
    while (stack1->next!=NULL||stack2->next!=NULL)
    {
        while (stack1->next!=NULL)
        {
            Tree top=pop(stack1);//pop and print top node
            if(top->right!=NULL) push(top->right,stack2);
            if(top->left!=NULL) push(top->left,stack2);
            //each child of top node entry stack2 in order from right to left
        }
        while (stack2->next!=NULL)
        {
            Tree top=pop(stack2);//pop and print top node
            if(top->left!=NULL) push(top->left,stack1);
            if(top->right!=NULL) push(top->right,stack1);
            //each child of top node entry stack1 in order from left to right
        }
    }
}
void buildtree(int index[],int postorder[],int head,int foot,Tree T)//还需分配内存
{
    int max=0,center,i;
    for(i=head;i<=foot;i++)
    {
        if(index[i]>=max)
        {
            max=index[i];
            center=i;
        }
    }
    T->element=postorder[max];
    T->left=NULL;
    T->right=NULL;
    T->next=NULL;
    //printf("%d ",postorder[max]) ;
    if(center-1>=head) 
    {
    	//Tree L=(Tree)malloc(sizeof(struct TreeNode));
    	T->left=(Tree)malloc(sizeof(struct TreeNode));
		buildtree(index,postorder,head,center-1,T->left);
    }
    if(center+1<=foot)
    {
    	//Tree R=(Tree)malloc(sizeof(struct TreeNode));
    	T->right=(Tree)malloc(sizeof(struct TreeNode));
		buildtree(index,postorder,center+1,foot,T->right);
    }
}
void push(Tree T,Tree S)
{
    T->next=S->next;
    S->next=T;
}
Tree pop(Tree S)
{
	static int i=0;
	Tree top;
	top=S->next;
	S->next=top->next;
	if(!i++) printf("%d",top->element);
	else printf(" %d",top->element);
	return top;
}
