# 해결 
도시가 연결 되어 있으면 하나의 집합에 속하게 된다.
이런 점에서 상호 배타적 집합을 구조체로 구현해야겠다는 생각을 했다.  

두 개의 집합이 연결되었을때 두 쌍을 중복되어 계산할 수 있다.  
이를 피하기 위해 u가 v보다 작은 경우만 합치는 연산을 실행했다.  
```c++
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
```
