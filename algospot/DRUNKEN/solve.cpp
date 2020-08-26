#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF=987654321;
const int MAX_V=501;

int V;
int adj[MAX_V][MAX_V];
int W[MAX_V][MAX_V];
int delay[MAX_V];

void makeGraph()
{
    int E;
    cin>>V>>E;
    
    for(int i=0;i<V;++i)
        cin>>delay[i];
    
    for(int i=0;i<V;++i)
        for(int j=0;j<V;++j)
        {
            adj[i][j]=INF;
            W[i][j]=INF;
        }
    
    for(int i=0;i<E;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        --a; --b;
        adj[a][b]=c;
        adj[b][a]=c;
        W[a][b]=c;
        W[b][a]=c;
    }
}

void floyd()
{
    vector<pair<int,int> > order;
    for(int i=0;i<V;++i)
    {
        adj[i][i]=0;
        W[i][i]=0;
        order.push_back(make_pair(delay[i],i));
    }
    sort(order.begin(),order.end());
    for(int k=0;k<V;++k)
    {
        int w=order[k].second;
        for(int i=0;i<V;++i)
            for(int j=0;j<V;++j)
            {
                adj[i][j]=min(adj[i][j],adj[i][w]+adj[w][j]);
                W[i][j]=min(W[i][j],adj[i][w]+delay[w]+adj[w][j]);
            }
    }
}

int main()
{
    makeGraph();
    floyd();
    
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int s,t;
        cin>>s>>t;
        --s; --t;
        
        cout<<W[s][t]<<endl;
    }
    
    return 0;
}
