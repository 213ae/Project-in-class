#include <stdio.h>
int M,N,K;//M（堆栈的最大容量）,N（推送序列的长度）, K（要检查序列的数量）
void check(int a[]);
int main()
{
	int i,j;
	scanf("%d %d %d",&M,&N,&K);
	int a[K][N];
	for(i=0;i<K;i++)
	{
		for(j=0;j<N;j++)
		scanf("%d",&a[i][j]);
	}
	for(i=0;i<K;i++)
	{
		check(a[i]);
		if(i!=K-1) printf("\n");
	}
	return 0;
} 
void check(int a[])
{
	int stack[1000];
	int max=0,n=-1,flag=1,k,j;
	for(j=0;j<N;j++)
	{
		if(a[j]>max)
		{
			for(k=max+1;k<a[j];k++)
			{
				n++;
				stack[n]=k;
				if(n>=M-1) 
				{
					flag=0;
					break;
				}
			} 
			max=a[j];
		}
		else
		{
			if(a[j]==stack[n]) 
			{
				n--;
			}
			else
			{
				flag=0;
				break;
			}
		}
	}
	if(flag==1)
		printf("YES");
	else
		printf("NO");
}
