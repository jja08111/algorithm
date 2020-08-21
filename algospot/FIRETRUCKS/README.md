# 해결 
소방서들을 기준으로 다익스트라 알고리즘을 이용하여 최단거리를 계산했다.   

처음에는 우선순위 큐인 pq에 하나씩 소방서 위치를 시작점으로 넣으며 최신화 하는 방식을 선택했다.  
그런데 이는 pq에 모든 소방서들을 한번에 넣어 알고리즘을 돌리면 같은 방식으로 동작한다.  
따라서 더욱 간단한 방식인 후자의 방식을 택했다.  
```c++
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_V=1001;
const int INF=987654321;

int V;
vector<pair<int,int> > adj[MAX_V];
vector<int> fire,station;

void readData()
{
    int e,n,m;
    cin>>V>>e>>n>>m;
    for(int i=0;i<e;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back(make_pair(b,c));
        adj[b].push_back(make_pair(a,c));
    }
    for(int i=0;i<n;++i)
    {
        int a; cin>>a;
        fire.push_back(a);
    }
    for(int i=0;i<m;++i)
    {
        int a; cin>>a;
        station.push_back(a);
    }
}

void update(vector<int>& dist, priority_queue<pair<int,int> >& pq)
{
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
}

int sumArrivalTime()
{
    vector<int> dist(V+1,INF);
    priority_queue<pair<int,int> > pq;
    
    for(int i=0;i<station.size();++i)
    {
        pq.push(make_pair(0,station[i]));
        dist[station[i]]=0;
    }
    update(dist,pq);
    
    int ret=0;
    for(int i=0;i<fire.size();++i)
        ret+=dist[fire[i]];
    
    return ret;
}

void clearData()
{
    for(int i=0;i<V+1;++i)
        adj[i].clear();
    fire.clear(); station.clear();
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        readData();
        cout<<sumArrivalTime()<<endl;
        
        clearData();
    }

    return 0;
}
```
