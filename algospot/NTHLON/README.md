# 해결 
코스에서 종목의 순서는 중요하지 않다. 코스에서 두 선수의 시간이 같기만 하면 된다.  
따라서 각 종목에서 두 선수의 시간 차이를 이용하여 그래프를 만드는 것이 핵심이다.  

즉, 정점을 시간차들의 합으로 하고, 간선의 가중치를 A국 선수가 각 종목에서 소요되는 시간으로 설정하면 된다.  
이때 도착점은 0이 되는데 시작점을 0으로 할 경우 하나 이상의 종목을 골라야 한다는 조건을 무시하게 된다.  
이는 시작점을 임의의 값 401로 하여 이 정점에서 나아가는 간선을 추가하여 해결하면 된다.  

그런데 어느 종목을 여러번 선택해도 되기 때문에 그래프의 크기가 무한해진다.  
이를 해결하는 방법은 한 종목당 200이상 소요되지 않기 때문에 -200에서 200으로 정점의 크기를 제한을 두는 것이다.  

위와 같은 방식으로 그래프를 생성하여 다익스트라 알고리즘을 이용하면 해결할 수 있다.  
아래의 코드에서 -200인 값을 인덱스로 나타내기 위해 변환하는 함수를 만든 것과, 시작점을 401로 설정한 것을 눈여겨 볼 필요가 있다.  
```c++
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF=987654321;

int V;
vector<pair<int,int> > adj[410];
const int START=401;

int vertex(int delta)
{
    return delta+200;
}

vector<int> dijkstra(int src)
{
    vector<int> dist(V,INF);
    dist[src]=0;
    priority_queue<pair<int,int> > pq;
    pq.push(make_pair(0,src));
    while(!pq.empty())
    {
        int cost=-pq.top().first;
        int here=pq.top().second;
        pq.pop();
        if(dist[here]<cost)
            continue;
        for(int i=0;i<adj[here].size();++i)
        {
            int there=adj[here][i].first;
            int nextDist=cost+adj[here][i].second;
            if(dist[there]>nextDist)
            {
                dist[there]=nextDist;
                pq.push(make_pair(-nextDist,there));
            }
        }
    }
    return dist;
}

int solve(const vector<int>& a, const vector<int>& b)
{
    V=402;
    for(int i=0;i<V;++i) 
        adj[i].clear();
    for(int i=0;i<a.size();++i)
    {
        int delta=a[i]-b[i];
        adj[START].push_back(make_pair(vertex(delta),a[i]));
    }
    for(int delta=-200;delta<=200;++delta)
    {
        for(int i=0;i<a.size();++i)
        {
            int next=delta+a[i]-b[i];
            if(abs(next)>200)
                continue;
            adj[vertex(delta)].push_back(make_pair(vertex(next),a[i]));
        }
    }
    vector<int> shortest=dijkstra(START);
    int ret=shortest[vertex(0)];
    if(ret==INF)
        return -1;
    return ret;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int n;
        cin>>n;
        
        vector<int> a(n),b(n);
        for(int i=0;i<n;++i)
            cin>>a[i]>>b[i];
        
        int ret=solve(a,b);
        if(ret==-1)
            cout<<"IMPOSSIBLE"<<endl;
        else
            cout<<ret<<endl;
    }
    return 0;
}
```
