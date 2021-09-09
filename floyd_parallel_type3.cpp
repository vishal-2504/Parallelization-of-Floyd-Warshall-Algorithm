//Parallel C Program for Floyd Warshall Algorithm (Column-major partition)
#include<bits/stdc++.h>
#include<omp.h>
#define INF 100000000.00
using namespace std;

int n,m;
//Number of vertices=n & no. of edges=m

void floydWarshall(int num, float *adj, float *dist)
{
	int k;
	for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            //dist[i][j] = adj[i][j];
            *(dist + i * n + j) = *(adj + i * n + j);
        }
        *(dist + i * n + i) = 0.00;
    }
    omp_set_num_threads(num);
    for(k=1;k<=n;k++)
    {
        #pragma omp parallel
        {    
          int i,j,id,nthreads,y; 
          id=omp_get_thread_num();
          nthreads=omp_get_num_threads();
          y=n/nthreads;
          id++;
          int z=id*y;
          if(id==nthreads)
           z=n;
          for(j=(id-1)*y+1;j<=z;j++)
          {
              for(i=1;i<=n;i++)
              {
                  if (*(dist + i * n + k) + *(dist + k * n + j) < *(dist + i * n + j))
                        *(dist + i * n + j) = *(dist + i * n + k) + *(dist + k * n + j);
              }
          }
        }
    }

    //print the output by removing the commments
    /*for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (*(dist + i * n + j) != INF)
                printf("%f ", *(dist + i * n + j));
            else
                printf("INF  ");
        }
        printf("\n");
    }*/
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int i,u,v;
    float w;  
    cin>>n>>m; //no of vertices and no of edges
    //input in the format directed edge from u to v with weight w
    float *adj = (float *)malloc((n + 1) * (n + 1) * sizeof(float));
    float *dist = (float *)malloc((n + 1) * (n + 1) * sizeof(float));
    for(u=0;u<=n;u++)
    {
        //adj[u].resize(n+1);
        for (v = 0; v <= n; v++)
            *(adj + u * n + v) = INF;
    }
    for(i=0;i<m;i++)
    {
        cin >> u >> v >> w;
        *(adj + u * n + v) = w;
        //adj[u][v]=w;
    }
    for(i=2;i<=32;i=i*2)
    {
      
      double start_time=omp_get_wtime();
  	  floydWarshall(i,adj,dist);     // i is the number of threads
  	  double end_time=omp_get_wtime()-start_time;
      double wall_clock=end_time;
      printf("%d %.10lf\n",i,wall_clock);
   }
	  return 0;
}
