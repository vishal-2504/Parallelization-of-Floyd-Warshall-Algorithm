//Parallel Cpp Program for Floyd Warshall Algorithm (2D-matrix Partition)
#include <bits/stdc++.h>
#include <omp.h>
#define INF 100000000.00
using namespace std;

int n, m;
//Number of vertices=n & no. of edges=m

void floydWarshall(int num, float *adj, float *dist)
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
    omp_set_num_threads(num);
    for (k = 1; k <= n; k++)
    {
        #pragma omp parallel
        {
            int i, j, id, nthreads, y;
            id = omp_get_thread_num();
            nthreads = omp_get_num_threads();
            y = n / nthreads;
            id++;
            if (id % 2 == 1)
            {
                int z = (id - 1) * y + (2 * y);
                if (id > nthreads - 2)
                    z = n;
                for (i = (id - 1) * y + 1; i <= z; i++)
                {
                    //float x=dist[i][k];
                    float x = *(dist + i * n + k);
                    for (j = 1; j <= n / 2; j++)
                    {
                        if (x + *(dist + k * n + j) < *(dist + i * n + j))
                            *(dist + i * n + j) = x + *(dist + k * n + j);
                    }
                }
            }
            else
            {
                int z = (id - 2) * y + (2 * y);
                if (id > nthreads - 2)
                    z = n;
                for (i = (id - 2) * y + 1; i <= z; i++)
                {
                    float x = *(dist + i * n + k);
                    for (j = n / 2 + 1; j <= n; j++)
                    {
                        if (x + *(dist + k * n + j) < *(dist + i * n + j))
                            *(dist + i * n + j) = x + *(dist + k * n + j);
                    }
                }
            }
        }
    }
    //print the output by removing the commments
    /*for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (dist[i][j] != INF)
                printf("%f ", dist[i][j]);
            else
                printf("INF  ");
        }
        printf("\n");
    }*/
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt","w",stdout);
    int u, v;
    float w;
    cin >> n >> m; //no of vertices and no of edges
    //input in the format directed edge from u to v with weight w
    float *adj = (float *)malloc((n + 1) * (n + 1) * sizeof(float));
    float *dist = (float *)malloc((n + 1) * (n + 1) * sizeof(float));
    for (u = 0; u <= n; u++)
    {
        //adj[u].resize(n+1);
        for (v = 0; v <= n; v++)
            *(adj + u * n + v) = INF;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        *(adj + u * n + v) = w;
        //adj[u][v]=w;
    }
    for (int i = 2; i <= 32; i = i * 2)
    {

        double start_time = omp_get_wtime();
        floydWarshall(i, adj, dist); // i is the number of threads
        double end_time = omp_get_wtime() - start_time;
        double wall_clock = end_time;
        printf("%d %.10lf\n", i, wall_clock);
    }
    free(adj);
    free(dist);
    return 0;
}
