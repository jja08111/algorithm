# 해결 
음수인 가중치를 가진 간선이 있는 문제이므로 밸만 포드 알고리즘을 이용하여 해결하면 된다.  

하지만 주의할 부분이 꽤 있다.  

1. **음수 사이클이 발견 되어 과거로 무한히 가는 경우 시작점과 그 사이클이 끊어져 있을 수 있다.**  
이 부분은 reachable이라는 배열을 그래프 생성시 정점간에 연결여부를 저장하면 해결 할 수 있다.  

2. **upper값이 underflow될 수 있다.**  
왜 이러한 일이 발생하냐면 각 정점을 반복하여 돌리면 int 범위보다 더 낮은 값이 나올 수 있기 때문이다. [여기](https://www.acmicpc.net/board/view/55270)에서
 잘 설명 되어있다.
```c++
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits>
using namespace std;

const int INF=987654321;//numeric_limits<long long>::max();
const int MAX_V=501;
const int START=1;

vector<pair<int,int> > adj[MAX_V];
bool reachable[MAX_V][MAX_V];
int V;

void makeGraph()
{
    int E;
    cin>>V>>E;
    
    memset(reachable,false,sizeof(reachable));
    for(int i=1;i<=V;++i)
        reachable[i][i]=true;
    
    for(int i=0;i<E;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back(make_pair(b,c));
        reachable[a][b]=true;
    }
    
    for(int k=1;k<=V;++k)
        for(int i=1;i<=V;++i)
            for(int j=1;j<=V;++j)
                reachable[i][j]|=reachable[i][k]&&reachable[k][j];
}

vector<long long> getMinTime()
{
    vector<long long> upper(V+1,INF);
    upper[START]=0;
    for(int it=0;it<V-1;++it)
        for(int here=1;here<=V;++here)
        {
            if(upper[here]==INF)
                continue;
            for(int i=0;i<adj[here].size();++i)
            {
                int there=adj[here][i].first;
                int cost=adj[here][i].second;
                upper[there]=min(upper[there],cost+upper[here]);
            }
        }
    for(int here=1;here<=V;++here)
        for(int i=0;i<adj[here].size();++i)
        {
            int there=adj[here][i].first;
            int cost=adj[here][i].second;
            if(reachable[START][there] && upper[there]>cost+upper[here])
            {
                upper.clear();
                return upper;
            }
        }
    return upper;
}

int main()
{
    makeGraph();
    
    vector<long long> dist=getMinTime();
    
    if(dist.empty())
        cout<<-1<<endl;
    else
        for(int i=2;i<=V;++i)
        {
            if(dist[i]==INF)
                cout<<-1<<endl;
            else
                cout<<dist[i]<<endl;
        }
    
    return 0;
}

```
