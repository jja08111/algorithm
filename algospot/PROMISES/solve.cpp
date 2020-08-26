#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF=987654321;
const int MAX_V=200;

int V,N;
int adj[MAX_V][MAX_V];

void makeGraph()
{
    int m;
    cin>>V>>m>>N;
    for(int i=0;i<V;++i)
        for(int j=0;j<V;++j)
            adj[i][j]=INF;
    
    for(int i=0;i<m;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        // 같은 간선에 다른 값이 주어질 수 있다.
        if(adj[a][b]>c)
            adj[a][b]=adj[b][a]=c;
    }
}

void floyd()
{
    for(int i=0;i<V;++i)
        adj[i][i]=0;
    for(int k=0;k<V;++k)
        for(int i=0;i<V;++i)
            for(int j=0;j<V;++j)
                adj[i][j]=min(adj[i][j],adj[i][k]+adj[k][j]);
}

bool update(int a, int b, int c)
{
    if(adj[a][b]<=c)
        return false;
    
    for(int i=0;i<V;++i)
        for(int j=0;j<V;++j)
            adj[i][j]=min(adj[i][j],
                          min(adj[i][a]+c+adj[b][j],
                              adj[i][b]+c+adj[a][j]));
    return true;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        makeGraph();
        floyd();
        
        int ret=0;
        for(int i=0;i<N;++i)
        {
            int a,b,c;
            cin>>a>>b>>c;
            
            if(!update(a,b,c))
                ++ret;
        }
        cout<<ret<<endl;
    }
    
    return 0;
}
