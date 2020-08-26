#include <iostream>
#include <vector>
using namespace std;

const int MAX_V=101;
const int INF=987654321;

int V;
int adj[MAX_V][MAX_V];

void floyd()
{
    for(int k=0;k<V;++k)
        for(int i=0;i<V;++i)
            for(int j=0;j<V;++j)
                adj[i][j]=min(adj[i][j],adj[i][k]+adj[k][j]);
}

void printResult()
{
    for(int i=0;i<V;++i)
    {
        for(int j=0;j<V;++j)
            cout<<(adj[i][j]==INF ? 0:1)<<' ';
        cout<<endl;
    }
}

int main()
{
    cin>>V;
    for(int i=0;i<V;++i)
        for(int j=0;j<V;++j)
        {
            cin>>adj[i][j];
            if(adj[i][j]==0)
                adj[i][j]=INF;
        }
    
    floyd();
    printResult();
    return 0;
}
