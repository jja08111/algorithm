#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

const int MAX_V=1001;
const double INF=numeric_limits<double>::max( );

int V,E;
int X[MAX_V], Y[MAX_V];
double adj[MAX_V][MAX_V];

double calcDist(int u, int v)
{
    return adj[u][v]=adj[v][u]=sqrt(pow(X[u]-X[v],2)+pow(Y[u]-Y[v],2));
}

double prim()
{
    vector<double> minDist(V,INF);
    vector<bool> added(V,false);
    
    double ret=0.0;
    minDist[0]=0;
    for(int it=0;it<V;++it)
    {
        int u=-1;
        for(int v=0;v<V;++v)
            if(!added[v] && (u==-1 || minDist[u]>minDist[v]))
            {
                u=v;
                if(minDist[u]==0)
                    break;
            }
        
        added[u]=true;
        ret+=minDist[u];
        for(int v=0;v<V;++v)
        {
            if(added[v])
                continue;
            double dist=(adj[u][v]==INF) ? calcDist(u,v) : adj[u][v];
            minDist[v]=min(minDist[v],dist);
        }
    }
    return ret;
}

int main()
{
    cin>>V>>E;
    
    for(int i=0;i<V;++i)
        cin>>X[i]>>Y[i];
    
    for(int i=0;i<V;++i)
        for(int j=0;j<V;++j)
            adj[i][j]=INF;
    
    for(int i=0;i<E;++i)
    {
        int a,b;
        cin>>a>>b;
        --a; --b;
        adj[a][b]=adj[b][a]=0;
    }
    cout<<fixed;
    cout.precision(2);
    cout<<prim()<<endl;

    return 0;
}
