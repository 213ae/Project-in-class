#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	srand((unsigned)time(NULL));
	int n, i, j;
	int Ns = 1000;
	int Na = 10;
	int M = 6000;
	int K = rand()%10+2;
	printf("%d %d\n",Ns,Na);
	for(i=1;i<=Na;i++)
	{
		printf("%d ", rand()%(Ns+Na)+1);
	}
	printf("\n");
	printf("%d\n",M);
	for(i=1;i<=M;i++)
	{
		n = rand()%(Ns+Na)+1;
		j = rand()%(Ns+Na)+1;
		if(n>Ns) printf("A-%d ", n-Ns);
		else printf("%d ", n);
		if(j>Ns) printf("A-%d ", j-Ns);
		else printf("%d ", j);
		printf("%d\n", rand()%10+1);
	}
	printf("%d\n",K);
	for(i=1;i<=K;i++)
	{
		printf("%d ", rand()%(Ns)+1);
	}
	printf("\n");
	
	
	
	
}
