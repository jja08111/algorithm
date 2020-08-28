#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct DisjointSet
{
    vector<int> parent, rank;
    DisjointSet(int n) : parent(n), rank(n,1)
    { 
        for(int i=0;i<n;++i)
            parent[i]=i;
    }
    int find(int u)
    {
        if(u==parent[u]) return u;
        return parent[u]=find(parent[u]);
    }
    void merge(int u, int v)
    {
        u=find(u); v=find(v);
        if(u==v)
            return;
        if(rank[u]>rank[v])
            swap(u,v);
        parent[u]=v;
        if(rank[u]==rank[v])
            ++rank[v];
    }
};

const int MAX_V=501;

int V;
int pos[MAX_V][2];

double kruskal(DisjointSet& sets)
{
  	double ret=0;
    vector<pair<double,pair<int,int> > > edges;
    for(int u=0;u<V;++u)
        for(int v=u+1;v<V;++v)
        {
            double cost=sqrt(pow(pos[u][0]-pos[v][0],2)+pow(pos[u][1]-pos[v][1],2));
            edges.push_back(make_pair(cost,make_pair(u,v)));
        }
    sort(edges.begin(), edges.end());
    
    for(int i=0;i<edges.size();++i)
    {
        double cost=edges[i].first;
        int u=edges[i].second.first, v=edges[i].second.second;
        if(sets.find(u)==sets.find(v))
            continue;
        ret+=cost;
        sets.merge(u,v);
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
        
        for(int i=0;i<2;++i)
            for(int k=0;k<V;++k)
            {   
                int p; cin>>p;
                pos[k][i]=p;
            }
        
        DisjointSet sets(V);
        for(int i=0;i<m;++i)
        {
            int u,v;
            cin>>u>>v;
            sets.merge(u,v);
        }
        
        cout<<kruskal(sets)<<endl;
    }

    return 0;
}
