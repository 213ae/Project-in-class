#include <stdio.h>
int N,K;//N（推送序列的长度）, K（要检查序列的数量）
void check(int position[]);
int main()
{
	int i,j,k;
	scanf("%d%d",&N,&K);
	int ori[N],position[K][N];
	for(j=0;j<N;j++)
	scanf("%d",&ori[j]);
	for(i=0;i<K;i++)
	{
		for(j=0;j<N;j++)
		{
			scanf("%d",&position[i][j]);
			for(k=0;k<N;k++)
			{
				if(position[i][j]==ori[k]) position[i][j]=k+1;
				break;
			}
		}
	}
//	for(i=0;i<K;i++)
//	{
//		for(j=0;j<N;j++)
//		printf("%d",position[i][j]);
//	}
	for(i=0;i<K;i++)
	{
		check(position[i]);
		if(i!=K-1) printf("\n");
	}
	return 0;
} 
void check(int position[])
{
	int stack[100];
	int max=0,head=-1,tail=0,flag=1,k,j;
	for(j=0;j<N;j++)
	{
		if(position[j]>max)
		{
			for(k=max+1;k<position[j];k++)
			{
				head++;
				stack[head]=k;
				printf("%d",1);
			} 
			max=position[j];
		}
		else
		{
			if(position[j]==stack[head]) 
			{
				head--;
				printf("%d",2);
			}
			else if(position[j]==stack[tail]&&head!=tail)
			{
				tail++;
				printf("%d",3);
			}
			else
			{
				flag=0;
				break;
			}
		}
	}
	if(flag==1)
		printf("yes");
	else
		printf("no");
}
