#include<stdio.h>
#define V 50
#define INF 99999


int dist[V][V];

//void printSolution(int dist[][V]);


void floydWarshall(int graph[][V])
{
	int i, j, k;

	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			dist[i][j] = graph[i][j];


	for (k = 0; k < V; k++)
	{
		for (i = 0; i < V; i++)
		{
			for (j = 0; j < V; j++)
			{
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}

}

/*
void printSolution(int dist[V][V])
{
	printf ("The following matrix shows the shortest distances"
			" between every pair of locations \n");
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			if (dist[i][j] == INF)
				printf("%7s", "INF");
			else
				printf ("%7d", dist[i][j]);
		}
		printf("\n");
	}
}
*/

int main()
{
int graph[V][V],i,j;
FILE *fp;
fp = fopen("adjacency_matrix.txt","r");
while(!feof(fp))
{
   for(j=0;j<V;j++)
    {
        fscanf(fp,"%d",&graph[i][j]);
    }
    i++;
}

    floydWarshall(graph);
	fclose(fp);


	//printSolution(dist);
	return 0;
}

