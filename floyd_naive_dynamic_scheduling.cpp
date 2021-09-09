//Parallel CPP Program for Floyd Warshall Algorithm
#include<bits/stdc++.h>
#include<omp.h>
#define INF 100000000.00
using namespace std;

vector< vector<float> > adj,dist;
int n,m;
//Number of vertices=n & no. of edges=m

void floydWarshall(int num)
{
	int i, j, k;
	#pragma omp parallel for private(i,j) num_threads(num)
	for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            dist[i][j]=adj[i][j];
        }
        dist[i][i]=0.0;
    }
    
    for(k=1;k<=n;k++)
    {
        #pragma omp parallel for schedule(dynamic,n/num) private(i,j) num_threads(num)      
        for(i=1;i<=n;i++)
        {
            float x=dist[i][k];
            for(j=1;j<=n;j++)
            {
                if(x+dist[k][j]<dist[i][j])
                 dist[i][j]=x+dist[k][j];
            }
        }
    }

    //print the output by removing the commments
    /*for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            cout<<dist[i][j]<<" ";
        }
        cout<<"\n";
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
    adj.clear();
    adj.resize(n+1);
    for(u=0;u<=n;u++)
    {
        adj[u].resize(n+1);
        for(v=0;v<=n;v++)
         adj[u][v]=INF;
    }
    for(i=0;i<m;i++)
    {
        cin>>u>>v>>w;
        adj[u][v]=w;
    }
    for(i=2;i<=32;i=i*2)
    {
      dist.clear();
      dist.resize(n+1);
      for(u=0;u<=n;u++)
      {
          dist[u].resize(n+1);
      }
      double start_time=omp_get_wtime();
  	  floydWarshall(i);     // i  is the number of threads
  	  double end_time=omp_get_wtime()-start_time;
      double wall_clock=end_time;
      printf("%d %.10lf\n",i,wall_clock);
   }
	return 0;
}
