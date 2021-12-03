#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define max_Na 20
#define max_Ns 2000
#define max_dist 2000000
typedef struct Edge *EPtr;
typedef struct vertex *VPtr;
struct Edge{
	int spot;//number from 1 to Ns represent pick-up spots, number from Ns+1 to Ns+Na represent ambulance dispatch centers
	int dist;//the distance between this vertex and another vertex adjacent to it
    EPtr next;
};
struct vertex{
    char spot[8];//the codename of this vertex
	int num;//the number of ambulance and it is 0 if the vertex is a pick-up spot
    int known[max_Na];//to confirm whether this vertex can be reached by one ambulance dispatch center
    VPtr path[max_Na];//store the previous vertex
    int edge[max_Na];//the edges between this vertex and Na ambulance dispatch centers
	int dist[max_Na];//the distance between this vertex and Na ambulance dispatch centers
	EPtr Adja;//point to the edges adjacent to this vertex
};//include all pick-up spots and ambulance dispatch centers

int read(int Ns);//return index corresponding to the codename of this vertex
void link(VPtr V, int spot, int dist);//link spots to each other when draw the gragh
void drawpath(VPtr V, int A);//output the path from this vertex to one center through finding the previous vertex constantly
void Dijkstra(VPtr V[], int i, int Ns);//traverse the whole gragh and find the shortest path of every vertex from every center

void enHeap(VPtr V, int A);
void Decrease(VPtr V, int A);
VPtr Deletemin(int A);
//function of heap
VPtr Heap[max_Ns] = {0};
int size_H = 0;
VPtr V[max_Ns];

int main2()
{
	int Ns, Na, M, K;
    int i, j;
    scanf("%d%d", &Ns, &Na);
    /*index from 1 to Ns represent pick-up spots 
    index from Ns+1 to Ns+Na represent ambulance dispatch centers*/
    for(i=1;i<=Ns+Na;i++)//initialize every vertex
    {
    	V[i] = (VPtr)calloc(1,sizeof(struct vertex));
        if(i <= Ns) sprintf(V[i]->spot,"%d",i);
        else sprintf(V[i]->spot,"A-%d",i-Ns);
        for(j=1;j<=Na;j++)
		{
			V[i]->dist[j] = max_dist;
			if(i-Ns == j) //one center to itself
			{
				V[i]->dist[j] = 0;
				V[i]->known[j] = 1;
			}
		}
    }
    for(i=1;i<=Na;i++)//number of ambulances
    {
        scanf("%d", &V[i+Ns]->num);
    }
    scanf("%d", &M);//number of edges
    for(i=1;i<=M;i++)
    {
        int spot1 = read(Ns), spot2 = read(Ns), dist;
        scanf("%d",&dist);
        link(V[spot1], spot2, dist);
        link(V[spot2], spot1, dist);
    }
    for(i=1;i<=Na;i++)
    {
        Dijkstra(V, i, Ns);
    }
    scanf("%d",&K);//number of calls
    for(i=1;i<=K;i++)
    {
        int spot;
        scanf("%d",&spot);
        int shortest = max_dist, shortest_A = 0;
        for(j=1;j<=Na;j++)//find the nearest center
        {
            if(V[spot]->known[j] == 1)
            {
                if(V[spot]->dist[j] < shortest)
                {
                    shortest = V[spot]->dist[j];
                    shortest_A = j;
                }
                else if(V[spot]->dist[j] == shortest)//if distance from two centers to this vertex is the same, find the one have more ambulances
                {
                    if(V[Ns+shortest_A]->num < V[Ns+j]->num) shortest_A = j;
                    else if(V[Ns+shortest_A]->num == V[Ns+j]->num)//if the number of ambulances is the same, find the one pass through less strests
                    {
                        if(V[spot]->edge[shortest_A] > V[spot]->edge[j]) shortest_A = j; 
                    }
                    
                }
            }

        }
        if(shortest_A == 0) //shortest_A = 0 implies that there is no more ambulance to dispatch
        {
            printf("All Busy");
            return 0;
        }
        V[Ns+shortest_A]->num--;
        if(V[Ns+shortest_A]->num == 0)//if the number of ambulances in a center become 0, then all spots is unreachable to it->so we switch all spots' known[it] to 0
        {
            for(j=1;j<=Ns;j++)
            {
                V[j]->known[shortest_A] = 0;
            }
        }
        drawpath(V[spot],shortest_A);
        printf("%d\n",shortest);    
    }
    return 0;
}

int read(int Ns)
{
    int num;
    if (scanf("%d",&num)) return num;
    else scanf("%*c%*c%d",&num); return num+Ns;
}
void link(VPtr V, int spot, int dist)
{
    EPtr temp;
    temp = (EPtr)malloc(sizeof(struct Edge));
    temp->spot = spot;
    temp->dist = dist;
    temp->next = V->Adja;
    V->Adja = temp;
}
void drawpath(VPtr V, int A)
{
    VPtr temp = V;
    char spot[max_Ns][8], i = 0, flag = 1;
    while(temp != NULL)
    {   
    	i++;
        sprintf(spot[i],"%s",temp->spot);
        temp = temp->path[A];
    }
    for(;i>=1;i--)
    {
        printf("%s%s",flag?"":" ",spot[i]);
        flag = 0;
    }
    printf("\n");
}
void Dijkstra(VPtr V[], int i, int Ns)
{
	VPtr v, temp;
	Heap[0] = (VPtr)calloc(1,sizeof(struct vertex));//sentinel
	EPtr E;
	v = V[Ns+i];
	do{
		E = v->Adja;
		while(E != NULL)
		{
			if(!V[E->spot]->known[i])
			{
				if(V[E->spot]->dist[i] == max_dist)
				{
					V[E->spot]->dist[i] = v->dist[i]+E->dist;
					V[E->spot]->path[i] = v;
					V[E->spot]->edge[i] = v->edge[i]+1;
					enHeap(V[E->spot], i);				
				}
				else if(v->dist[i]+E->dist < V[E->spot]->dist[i])
				{
					V[E->spot]->dist[i] = v->dist[i]+E->dist;
					V[E->spot]->path[i] = v;
					V[E->spot]->edge[i] = v->edge[i]+1;
					Decrease(V[E->spot], i);
				}
			}
			E = E->next;
		};
		v = Deletemin(i);
        if (v == NULL) break;
		v->known[i] = 1;
	}while(1);
}

void enHeap(VPtr V, int A)
{
	int j;
	for(j=++size_H;V->dist[A] < Heap[j/2]->dist[A];j/=2)
	{
		Heap[j] = Heap[j/2];
	}
	Heap[j] = V;
}
void Decrease(VPtr V, int A)
{
	int i,j;
	for(i=1;i<=max_Ns;i++)
	{
		if(Heap[i] == V) break;
	}
	for(j=i;V->dist[A] < Heap[j/2]->dist[A];j/=2)
	{
		Heap[j] = Heap[j/2];
	}
	Heap[j] = V;
}
VPtr Deletemin(int A)
{
	VPtr min = Heap[1];
	int i, child;
	for(i=1;i*2<=size_H;i=child)
	{
		child = i*2;
		if(child!=size_H&&Heap[child+1]->dist[A]<Heap[child]->dist[A]) child++;
		if(Heap[size_H]->dist[A]>Heap[child]->dist[A]) Heap[i]=Heap[child];
		else break;
	}
	Heap[i] = Heap[size_H];
	Heap[size_H--] = NULL;
	return min;
}
