## 1. 동적 계획법
TSP2.cpp 참고

## 2. 현재까지 구한 최적해보다 나빠지면 그만두기
   - 2-a. 그중에서 나머지 거리를 최단거리 간선들과 현재까지의 거리를 더한 값이 최적해보다 크면 그만두기(단순한 휴리스틱) 
```c++
double simpleHeuristic(vector<bool>& visited)
{
    double ret=minEdge[0];
    for(int i=0;i<n;++i)
        if(!visited[i])
            ret+=minEdge[i];
    return ret;
}
```
## 3. 가까운 도시부터 방문하기  
```c++
double solve()
{
    for(int i=0;i<n;++i)
    {
        vector<pair<int,int> > order;
        for(int j=0;j<n;++j)
            if(i!=j)
                order.push_back(make_pair(dist[i][j],j));
        sort(order.begin(),order.end());
        nearest[i].clear();
        for(int j=0;j<n-1;++j)
            nearest[i].push_back(order[j].second);
    }
}
```
## 4. 지금까지 만든 경로의 부분 경로를 뒤집어 더 짧은 경로가 되버리면 그만두기  
```c++
bool pathReversePruning(const vector<int>& path)
{
    if(path.size()<4) return false;
    int b=path[path.size()-2];
    int q=path[path.size()-1];
    for(int i=0;i+3<path.size();++i)
    {
        int p=path[i];
        int a=path[i+1];
        if(dist[p][a]+dist[b][q]>dist[p][b]+dist[a][q])
            return true;
    }
    return false;
}
```
## 5. MST(최소스패닝트리)인 경로는 최적해보다 작은 점을 이용
도시들을 연결해 나가면서 이미 연결되어 있지 않을때 두 도시를 연결하고 도로의 길이를 더한다.  
위 과정을 "크루스칼의 스패닝 트리 알고리즘"을 이용한다.
```c++
struct DisjointSet
{
    int vilageNum, components;
    vector<int> parent,rank;
    
    DisjointSet(int n) : vilageNum(n), components(n), parent(n), rank(n)
    {
        for(int i=0;i<vilageNum;++i)
        {
            parent[i]=i;
            rank[i];
        }
    }
    //here가 포함된 집합의 대표를 반환
    int find(int here)
    {
        if(here==parent[here])
            return here;
        return parent[here]=find(parent[here]);
    }
    //a가 포함된 집합과 b가 포함된 집합을 합치고, 합칠수 있으면 참을 반환
    bool merge(int a, int b)
    {
        a=find(a);
        b=find(b);
        //두 도시가 이미 연결되어 있는 경우
        if(a==b)
            return false;
        if(rank[a]>rank[b])
            swap(a,b);
        parent[a]=b;
        if(rank[a]==rank[b])
            ++rank[b];
        components--;
        return true;
    }
};

// 간선의 길이, 간선의 두 정점
vector<pair<double,pair<int,int> > > edges;

double mstHeuristic(int here, const vector<bool>& visited)
{
    DisjointSet sets(n);
    double taken=0;
    for(int i=0;i<edges.size();++i)
    {
        int a=edges[i].second.first;
        int b=edges[i].second.second;
        if(a!=0 && a!=here && visited[a]) continue;
        if(b!=0 && b!=here && visited[b]) continue;
        if(sets.merge(a,b))
            taken+=edges[i].first;
    }
    return taken;
}
```

# 출처 

https://jaimemin.tistory.com/408  
크루스칼의 스패닝 트리 알고리즘, Disjoint Set구현을 위한 Union-find의 표현
https://www.weeklyps.com/entry/%ED%81%AC%EB%A3%A8%EC%8A%A4%EC%B9%BC-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-Kruskals-algorithm  
https://bowbowbow.tistory.com/26
