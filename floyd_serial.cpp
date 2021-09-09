//Serial Cpp Program for Floyd Warshall Algorithm
//Though this is a serial implementation, We are using the omp_get_wtime() function of the omp library for measuring the time. So compile and run the code accordingly

#include <bits/stdc++.h>
#include <omp.h>
#define INF 100000000.00
using namespace std;

int n, m;
//Number of vertices=n & no. of edges=m

void floydWarshall(float *adj, float *dist)
{
    int i, j, k;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            //dist[i][j] = adj[i][j];
            *(dist + i * n + j) = *(adj + i * n + j);
        }
        *(dist + i * n + i) = 0.00;
    }

    for (k = 1; k <= n; k++)
    {
        for (i = 1; i <= n; i++)
        {
            for (j = 1; j <= n; j++)
            {
                if (*(dist + i * n + k) + *(dist + k * n + j) < *(dist + i * n + j))
                    *(dist + i * n + j) = *(dist + i * n + k) + *(dist + k * n + j);
            }
        }
    }
    //print the output by removing the commments
    /*for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            cout<<*(dist + i * n + j)<<" ";
        }
        cout<<"\n";
    }*/
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int u, v;
    float w;
    cin >> n >> m; //no of vertices and no of edges
    //input in the format directed edge from u to v with weight w
    
    float *adj = (float *)malloc((n + 1) * (n + 1) * sizeof(float));
    float *dist = (float *)malloc((n + 1) * (n + 1) * sizeof(float));

    for (u = 0; u <= n; u++)
    {
        for (v = 1; v <= n; v++)
            *(adj + u * n + v) = INF;
        //adj[u][v] = INF;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        *(adj + u * n + v) = w;
        //adj[u][v] = w;
    }
    for (int num = 2; num <= 2; num++)
    {
        double start_time = omp_get_wtime();
        int p;
        for (p = 0; p < 1; p++)
        {
            floydWarshall(adj, dist);
        }
        double end_time = omp_get_wtime() - start_time;
        double wall_clock = end_time;
        printf("%.10lf\n", wall_clock / (float)(p));
        
    }
    free(adj);
    free(dist);
    //adj.clear();
    return 0;
}
