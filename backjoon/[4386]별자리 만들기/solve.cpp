#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX_V=101;
const int INF=987654321;

int V;
double adj[MAX_V][MAX_V];
double X[MAX_V], Y[MAX_V];

double calcDist(int u, int v)
{
    return adj[u][v]=adj[v][u]=sqrt(pow(X[u]-X[v],2)+pow(Y[u]-Y[v],2));
}

double prim()
{
    double ret=0.0;
    vector<double> minDist(V,INF);
    vector<bool> added(V,false);
    
    minDist[0]=0;
    for(int it=0;it<V;++it)
    {
        // 다음 간선 중 가중치가 최소인 간선을 찾는다.   
        int u=-1;
        for(int v=0;v<V;++v)
            if(!added[v] && (u==-1 || minDist[u]>minDist[v]))
                u=v;
        
        // 다음 정점을 트리에 추가한다.  
        ret+=minDist[u];
        added[u]=true;
        // 다음 정점과 이어진 간선들을 검사한다.
        for(int v=0;v<V;++v)
            if(!added[v])
            {
                // 거리가 계산되었다면 이용하고 아직 계산되지 않으면 계산한다. 
                double dist=(adj[u][v]==INF) ? calcDist(u,v) : adj[u][v];
                minDist[v]=min(minDist[v],dist);
            }
    }
    return ret;
}

int main()
{
    cin>>V;
    for(int i=0;i<V;++i)
        cin>>X[i]>>Y[i];
    
    for(int i=0;i<V;++i)
        for(int j=0;j<V;++j)
            adj[i][j]=INF;
    
    cout<<fixed;
    cout.precision(2);
    cout<<prim()<<endl;

    return 0;
}
