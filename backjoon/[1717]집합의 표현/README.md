# 해결 
한 원소는 다른 두 개 이상의 집합에 속할 수 없다. 즉, 상호 배타적인 집합을 형성하고 있다.  
이를 구조체로 구현하면 아래와 같다.  
합치기 연산과 집합을 찾는 연산을 할 수 있다.  
찾기 연산시 루트가 그 집합을 나타내는데 재귀 호출시 루트가 나온 경우 바로 대입하면서 찾기 연산을 할때마다 최적화를 진행하는 것을 볼 수 있다.  
합치기 연산은 트리가 한쪽으로 치우치지 않도록 rank를 생성해 더 낮은 트리를 더 높은 트리에 붙여서 최적화를 하고 있다.  

이 문제를 풀 때 parent의 index가 1,000,000까지 주어질 수 있으니 이점을 유의해야 한다.
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
```
