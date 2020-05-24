# 해결
모든 기지가 간접적으로라도 연결되어야 한다.  
중간에 두 기지가 닿을 수 있어야 한다.  

### 결정 문제
무전기의 통신 반경이 power라고 할때 모든 기지가 연결 되어 있는지 확인하기 위해서는 그래프의 너비 우선 탐색 알고리즘을 사용하면 된다.  
한 기지에서 시작해 다른 기지에도 방문 가능하면 연결되는 것이다.
```c++
bool decision(double power)
{
    //첫번째 기지 부터 방문
    vector<bool> visited(n,false);
    visited[0]=true;
    queue<int> q;
    q.push(0);
    int seen=0;
    while(!q.empty())
    {
        int here=q.front();
        q.pop();
        ++seen;
        for(int there=0;there<n;++there)
            if(!visited[there] && dist[here][there]<=power)
            {
                visited[there]=true;
                q.push(there);
            }
    }
    return seen==n;
}
```
### 이분법
```c++
double getMinPower()
{
    double lo=0, hi=1416.00;
    for(int iter=0;iter<100;++iter)
    {
        double mid=(lo+hi)/2.0;
        if(decision(mid))
            hi=mid;
        else
            lo=mid;
    }
    return hi;
}
```

# 회고
비트마스크를 이용하여 visited를 표현하려 했으나 기지가 100개가 넘는다는 사실을 뒤늦게 깨달아 한참 디버깅 했었다.
