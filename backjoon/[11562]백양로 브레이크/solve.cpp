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
