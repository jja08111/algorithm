# 해결 
최소 공통 조상(LCA)를 찾는 문제이다.  
알고스팟 사이트의 [FAMILYTREE](https://algospot.com/judge/problem/read/FAMILYTREE) 문제와 유사하다.  
[해결 방법](https://github.com/jja08111/algorithm/tree/master/algospot/FAMILYTREE)은 거의 유사하지만 트리를 탐색하며 trip을 형성하는 과정이 조금 다르다.  
그리고 찾는 값이 공통 최소 조상을 지나는 경로의 길이가 아닌 LCA 그 자체 이다.  

trip을 형성하는 방법이 다른 이유는 입력에 간선으로 이어지는 두 정점의 값들로 주어지기 때문이다.  
그렇기 때문에 visited 배열을 만들어 traverse에서 이미 방문한 경우 체크해서 DFS를 해야한다.   
```c++
vector<int> adj[MAX_N];
bool visited[MAX_N];
int serial2no[MAX_N], no2serial[MAX_N];
int locInTrip[MAX_N], depth[MAX_N];
int nextSerial;

void traverse(int here, int d, vector<int>& trip)
{
    visited[here]=true;
    
    no2serial[here]=nextSerial;
    serial2no[nextSerial]=here;
    ++nextSerial;
    
    depth[here]=d;
    locInTrip[here]=trip.size();
    trip.push_back(no2serial[here]);
    
    for(int i=0;i<adj[here].size();++i)
    {
        int cand=adj[here][i];
        if(!visited[cand])
        {
            traverse(cand,d+1,trip);
            trip.push_back(no2serial[here]);
        }
    }
}

RMQ* prepareRMQ() 
{
    nextSerial=0;
    vector<int> trip;
    // root부터 시작
    traverse(1,0,trip);
    return new RMQ(trip);
}
```

RMQ를 형성한 이후에는 주어지는 두 노드의 LCA를 찾으면 된다. 
이때 RMQ에는 순회한 결과를 serial number로 저장하고 있어 착각하지 않도록 유의해야 한다.  
```c++
int getLCA(RMQ* rmq, int u, int v)
{
    int lu=locInTrip[u], lv=locInTrip[v];
    if(lu>lv)
        swap(lu,lv);
    return serial2no[rmq->query(lu,lv)];
}
```
