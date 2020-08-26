#include <iostream>
#include <cstring>
using namespace std;

const int INF=987654321;
const int MAX_V=101;

int V;
int adj[MAX_V][MAX_V];

void floyd()
{
    for(int i=1;i<=V;++i)
        adj[i][i]=0;
    for(int k=1;k<=V;++k)
        for(int i=1;i<=V;++i)
            for(int j=1;j<=V;++j)
                adj[i][j]=min(adj[i][j],adj[i][k]+adj[k][j]);
}

int main()
{
    int E;
    cin>>V>>E;
    
    for(int i=1;i<=V;++i)
        for(int j=1;j<=V;++j)
            adj[i][j]=INF;
    
    for(int i=0;i<E;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        adj[a][b]=min(adj[a][b],c);
    }
    
    floyd();
    
    for(int i=1;i<=V;++i)
        for(int j=1;j<=V;++j)
        {
            if(adj[i][j]==INF)
                cout<<0<<' ';
            else
                cout<<adj[i][j]<<' ';
        }
        cout<<endl;
    
    return 0;
}
