#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct DisjointSet
{
    vector<int> parent,rank;
    DisjointSet(int n): parent(n), rank(n,1) 
    { 
        for(int i=0;i<n;++i)
            parent[i]=i;
    }
    int find(int u)
    {
        if(parent[u]==u)
            return u;
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

const int MAX_V=2001;
const int INF=987654321;

int V,E;
vector<pair<int,int> > adj[MAX_V];
vector<int> weights;
vector<pair<int,pair<int,int> > > edges;

int minUpperBound(int low)
{
    DisjointSet sets(V);
    for(int i=0;i<edges.size();++i)
    {
        if(edges[i].first<weights[low])
            continue;
        sets.merge(edges[i].second.first, edges[i].second.second);
        if(sets.find(0)==sets.find(V-1))
            return edges[i].first;
    }
    return INF;
}

int minWeightDifference()
{
    int ret=INF;
    for(int i=0;i<weights.size();++i)
        ret=min(ret,minUpperBound(i)-weights[i]);
    return ret;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>V>>E;
        for(int i=0;i<E;++i)
        {
            int a,b,c;
            cin>>a>>b>>c;
            
            adj[a].push_back(make_pair(b,c));
            adj[b].push_back(make_pair(a,c));
            
            weights.push_back(c);
            edges.push_back(make_pair(c,make_pair(a,b)));
            edges.push_back(make_pair(c,make_pair(b,a)));
        }
        sort(weights.begin(),weights.end());
        sort(edges.begin(),edges.end());
        
        cout<<minWeightDifference()<<endl;
        
        for(int i=0;i<V;++i)
            adj[i].clear();
        weights.clear();
        edges.clear();
    }
    return 0;
}
