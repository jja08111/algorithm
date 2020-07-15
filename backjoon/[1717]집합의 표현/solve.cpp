#include <iostream>
#include <vector>
using namespace std;

struct DisjointSet {
    vector<int> parent, rank;
    DisjointSet(int n) : parent(n+1), rank(n,1) {
        for(int i=0;i<=n;++i)
            parent[i]=i;
    }
    int find(int u) {
        if(parent[u]==u)
            return u;
        return parent[u]=find(parent[u]);
    }
    void merge(int u, int v) {
        u=find(u), v=find(v);
        if(u==v)
            return;
        
        if(rank[u]>rank[v])
            swap(u,v);
        parent[u]=v;
        if(rank[u]==rank[v])
            ++rank[v];
    }
};

int main()
{
    int n,m;
    cin>>n>>m;
    
    DisjointSet tree(n);
    
    for(int i=0;i<m;++i)
    {
        int p,a,b;
        scanf("%d %d %d",&p,&a,&b);
        
        if(p==0)
            tree.merge(a,b);
        else
        {
            int u=tree.find(a);
            int v=tree.find(b);
            printf("%s \n",(u==v) ? "YES" : "NO");
        }
    }

    return 0;
}
