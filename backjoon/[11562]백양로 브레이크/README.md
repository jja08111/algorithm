# 해결 
주어진 출발지와 목적지에서 몇 개의 역방향 도로를 이용해야 하는지 찾아야 한다.  

찾는 방법은 먼저 일방통행인 간선의 가중치를 1로 설정하고, 양방향인 간선은 0으로 설정한다.  
그 후 s와 e가 주어졌을 때 최단거리를 출력하면 된다.  
즉, 일방통행의 역방향을 이용할 때마다 1을 더하고, 이것이 최소가 되는 경로의 거리 값을 찾는 것이다.  

이 문제는 질문하는 학생의 수가 많으므로 입출력시 빠른 함수를 이용해야 한다.  
```c++
#include <iostream>
#include <vector>
using namespace std;

const int MAX_V=251;
const int INF=987654321;

int V;
int adj[MAX_V][MAX_V];

void makeGraph()
{
    int E;
    cin>>V>>E;
    for(int i=0;i<V;++i)
        for(int j=0;j<V;++j)
            adj[i][j]=(i==j) ? 0 : INF;
    
    for(int i=0;i<E;++i)
    {
        int u,v,isBidir;
        scanf("%d %d %d",&u,&v,&isBidir);
        --u; --v;
        adj[u][v]=0;
        adj[v][u]=(isBidir) ? 0 : 1;
    }
}

void floyd()
{
    for(int k=0;k<V;++k)
        for(int i=0;i<V;++i)
            for(int j=0;j<V;++j)
                adj[i][j]=min(adj[i][j],adj[i][k]+adj[k][j]);
}

int main()
{
    makeGraph();
    floyd();
    
    int n;
    cin>>n;
    while(n--)
    {
        int s,e;
        scanf("%d %d",&s,&e);
        --s; --e;
        printf("%d\n",adj[s][e]);
    }
    
    return 0;
}
```
