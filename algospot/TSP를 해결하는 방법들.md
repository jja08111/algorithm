## 1. 동적 계획법
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
https://jaimemin.tistory.com/408
https://www.weeklyps.com/entry/%ED%81%AC%EB%A3%A8%EC%8A%A4%EC%B9%BC-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-Kruskals-algorithm
https://bowbowbow.tistory.com/26
