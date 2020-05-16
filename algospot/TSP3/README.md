# 해결 
### 1. 동적 계획법
TSP2.cpp 참고  
하지만 이 방법으로는 공간,시간복잡도가  해결할 수 없다.

### 2. 현재까지 구한 최적해보다 나빠지면 그만두기
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
### 3. 가까운 도시부터 방문하기  
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
### 4. 지금까지 만든 경로의 부분 경로를 뒤집어 더 짧은 경로가 되버리면 그만두기  
```c++
bool pathReversePruning(const vector<int>& path)
{
    if(path.size()<4) 
        return false;
    
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
### 5. MST(최소스패닝트리)인 경로는 최적해보다 작은 점을 이용
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
            rank[i]=0;
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
        if(a==b)
            return false;
        if(rank[a]>rank[b])
            swap(a,b);
        parent[a]=b;
        if(rank[a]==rank[b])
            ++rank[b];
        --components;
        return true;
    }
};

// 간선의 길이, 간선의 두 정점
vector<pair<double,pair<int,int> > > edges;

double mstHeuristic(int here, int visited)
{
    DisjointSet sets(n);
    double taken=0;
    
    for(int i=0;i<edges.size();++i)
    {
        int a=edges[i].second.first;
        int b=edges[i].second.second;
        if(a!=here && (visited&(1<<a))) continue;
        if(b!=here && (visited&(1<<b))) continue;
        if(sets.merge(a,b))
            taken+=edges[i].first;
    }
    return taken;
}
```

### 6. 위 과정+메모이제이션 적용
메모리의 부족을 방지하기 위해 남은 도시의 수가 5개 이하일때만 메모이제이션을 적용한다.  
5라는 수는 실험을 통해 나온 최적의 결과라고 한다.  
cache를 배열이 아닌 연관배열인 map을 이용하였다.
```c++
const int CACHE_DEPTH=5;
//dp(here, visited)=cache[here][남은 도시의 수][visited]
map<int,double> cache[MAX][CACHE_DEPTH+1];

double dp(int here, int visited)
{
    if(visited==(1<<n)-1)
        return 0.0;
    
    int remaining=n-__builtin_popcount(visited);
    double& ret=cache[here][remaining][visited];
    if(ret>0)
        return ret;
    
    ret=INF;
    for(int next=0;next<n;++next)
    {
        if(visited&(1<<next))
            continue;
        ret=min(ret,dp(next,visited|(1<<next))+dist[here][next]);
    }
    return ret;
}
```
## 회고
교재는 문제가 시작위치로 다시 돌아오는 것이지만 온라인 문제는 한번씩만 방문하면 된다.  
따라서 아래의 두가지 경우를 유의해야 한다.  
- 함수 mstHeuristic의 if문의 조건중 a!=0과 같은 조건을 넣어서는 안된다.  
- 함수 dp에서 기저사례에 도달시 dist[here][0]이 아닌 0.0을 반환하여야 한다.  

위 두개의 조건을 디버깅 하느라 한참을 헤매었다.

## 출처 

https://jaimemin.tistory.com/408  
크루스칼의 스패닝 트리 알고리즘, Disjoint Set구현을 위한 Union-find의 표현
https://www.weeklyps.com/entry/%ED%81%AC%EB%A3%A8%EC%8A%A4%EC%B9%BC-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-Kruskals-algorithm  
https://bowbowbow.tistory.com/26
