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

int n,m;

bool areConnected(DisjointSet& tree) 
{
    int pivot;
    cin>>pivot;
    pivot=tree.find(pivot);
    for(int i=0;i<m-1;++i)
    {
        int next;
        scanf("%d",&next);
        next=tree.find(next);
        if(pivot!=next)
            return false;
    }
    return true;
}

int main()
{
    cin>>n>>m;
    
    DisjointSet tree(n);
    
    for(int u=1;u<=n;++u)
        for(int v=1;v<=n;++v)
        {
            int tmp;
            scanf("%d",&tmp);
            // 두 쌍을 모두 확인하지 않는다.
            if(u<v && tmp==1)
                tree.merge(u,v);
        }
    
    if(areConnected(tree))
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;

    return 0;
}
