# 해결 
플로이드의 알고리즘을 정확히 이해하면 해결할 수 있는 문제이다.  

새로운 간선이 추가되었을 때 그래프 갱신을 빠르게 해야 한다.  
다시 플로이드 알고리즘을 돌리는 것과 같은 무식한 방법으로는 알고리즘을 N번 돌려야 하는데 이는 시간안에 수행하기 어렵다.  

### 갱신된 간선을 지나는 경로만 최적화 
갱신된 간선을 지나지 않은 부분까지 갱신할 필요는 없다.  
즉, 모든 정점을 추가하며 경유지 집합을 늘려 나가지 않고 추가된 간선에 대해서만 업데이트 해주면 된다.  '
```c++
bool update(int a, int b, int c)
{
    if(adj[a][b]<=c)
        return false;
    
    for(int i=0;i<V;++i)
        for(int j=0;j<V;++j)
            adj[i][j]=min(adj[i][j], 
                          min(adj[i][a]+c+adj[b][j], // 추가된 간선(i->a~b->j or i->b~a->j)이 더 작은가?
                              adj[i][b]+c+adj[a][j]));
    return true;
}
```

### 주의사항 
구현시 주의할 점은 같은 간선에 대해 다른 값이 주어질 수 있어 더 작은 값인지 확인해야 한다.  
```c++
void makeGraph()
{
    int m;
    cin>>V>>m>>N;
    for(int i=0;i<V;++i)
        for(int j=0;j<V;++j)
            adj[i][j]=INF;
    
    for(int i=0;i<m;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        // 같은 간선에 다른 값이 주어질 수 있다.
        if(adj[a][b]>c)
            adj[a][b]=adj[b][a]=c;
    }
}
```
