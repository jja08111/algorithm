#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

const int INF=987654321;
const int MAX_V=501;

int V;
int adj[MAX_V][MAX_V];
int X[MAX_V];
int Y[MAX_V];

int calcDistSqr(const int u, const int v)
{
    return adj[u][v]=adj[v][u]=(pow(X[u]-X[v],2)+pow(Y[u]-Y[v],2));
}

double prim()
{
  	vector<bool> added(V,false);
  	vector<int> minDistSqr(V,INF), parent(V,-1);
  	double ret=0;
  	minDistSqr[0]=parent[0]=0;
  	for(int it=0;it<V;++it)
  	{
        int u=-1;
        for(int v=0;v<V;++v)
            if(!added[v] && (u==-1 || minDistSqr[u]>minDistSqr[v]))
            {       
                u=v;
                if(minDistSqr[u]==0) 
                    break;
            }
        
        ret+=sqrt(minDistSqr[u]);
        added[u]=true;
        
        for(int v=0;v<V;++v)
        {
            if(added[v])
                continue;
            
            int distSqr=adj[u][v]==INF ? calcDistSqr(u,v) : adj[u][v];
            if(minDistSqr[v]>distSqr)
            {
                parent[v]=u;
                minDistSqr[v]=distSqr;
            }
        }
  	}
  	return ret;
}

int main()
{
    int testCase;
    cin>>testCase;
    
    cout<<fixed;
    cout.precision(10);
    
    while(testCase--)
    {
        int m;
        cin>>V>>m;
        
        for(int i=0;i<V;++i)
            for(int j=0;j<V;++j)
                adj[i][j]=INF;
        
        for(int i=0;i<V;++i)
            cin>>X[i];
        for(int i=0;i<V;++i)
            cin>>Y[i];
        
        for(int i=0;i<m;++i)
        {
            int u,v;
            cin>>u>>v;
            adj[u][v]=adj[v][u]=0;
        }
        
        cout<<prim()<<endl;
    }

    return 0;
}
