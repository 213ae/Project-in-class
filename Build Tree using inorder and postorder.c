#include <stdio.h>
#include <stdlib.h>

#define MAXN 10

typedef struct TreeNode *Tree;
struct TreeNode {
    int Element;
    Tree  Left;
    Tree  Right;
};

Tree BuildTree( int inorder[], int postorder[], int N );

void Inorder_output( Tree T ); /* details omitted */
void Postorder_output( Tree T ); /* details omitted */

int main()
{
    Tree T;
    int inorder[MAXN], postorder[MAXN], N, i;

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &inorder[i]);
    for (i=0; i<N; i++) scanf("%d", &postorder[i]);
    T = BuildTree(inorder, postorder, N);
    printf("Check:\n");
	
    return 0;
}

/* Your function will be put here */
Tree BuildTree( int inorder[], int postorder[], int N )
{
    int i,j,inorder1[MAXN],inorder2[MAXN],postorder1[MAXN],postorder2[MAXN];
    Tree T=(Tree)malloc(sizeof(struct TreeNode));
    T->Element=postorder[N-1];
    printf("%d ",T->Element) ;
    for(i=0;i<N;i++)
    {
        if(inorder[i]==postorder[N-1]) break;
    }
    for(j=0;j<i;j++)
    {
        inorder1[j]=inorder[j];
        postorder1[j]=postorder[j];
    }
    for(j=i;j<N-1;j++)
    {
        inorder2[j-i]=inorder[j+1];
        postorder2[j-i]=postorder[j];
    }
    if(i>0) T->Left=BuildTree(inorder1,postorder1,i);
    if(N-i-1>0) T->Right=BuildTree(inorder2,postorder2,N-i-1);
    return T;
}
