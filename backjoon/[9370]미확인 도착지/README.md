# 해결 
문제를 이해하기 어려울 수 있다.  
적은 항상 최단경로로 목적지 후보들 중 하나로 이동한다.  
이때 g-h를 포함하는 경로여야 한다.  

즉, 목적지들 중 하나로 가는 최단경로가 g-h를 지나가는 경로인지 확인하는 문제이다.  

## 1. 쉬운 풀이
일반적인 풀이는 시작지점이 S라고 하고 목적지 중 하나를 D라고 하였을 때 아래 두 가지 중 더 빠른 경로가 S -> D의 최단 경로의 길이와 같아야 한다.  
- S -> g -> h -> D
- S -> h -> g -> D

위 두 가지 중 하나가 S -> D의 최단 경로와 같다면 해당 목적지는 후보가 되는 것이다.  
어느 간선을 지나는 경로를 구하는 방식은 코드를 보면 이해할 수 있다.
```c++
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX_V=2001;
const int INF=987654321;

int vertexNum,start;
int g,h,edgeGH;
vector<pair<int,int> > adj[MAX_V];
vector<int> destination;

void readData()
{
    int m,t;
    cin>>vertexNum>>m>>t;
    cin>>start>>g>>h;
    for(int i=0;i<m;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back(make_pair(b,c));
        adj[b].push_back(make_pair(a,c));
        if((a==g && b==h) || (a==h && b==g))
            edgeGH=c;
    }
    for(int i=0;i<t;++i)
    {
        int a; cin>>a;
        destination.push_back(a);
    }
}

vector<int> getDist(int src)
{
    vector<int> dist(vertexNum+1, INF);
    dist[src]=0;
    priority_queue<pair<int,int> > pq;
    pq.push(make_pair(0,src));
    while(!pq.empty())
    {
        int cost= -pq.top().first;
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

void clearData()
{
    for(int i=0;i<vertexNum+1;++i)
        adj[i].clear();
    destination.clear();
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        readData();
        vector<int> distStart=getDist(start);
        vector<int> distG=getDist(g);
        vector<int> distH=getDist(h);
        
        sort(destination.begin(),destination.end());
        for(int i=0;i<destination.size();++i)
        {
            int dest=destination[i];
            int minDist=distStart[dest];
            
            if((distStart[g]+edgeGH+distH[dest]==minDist) || 
                (distStart[h]+edgeGH+distG[dest]==minDist))
                cout<<dest<<' ';
        }
        
        cout<<endl;
        clearData();
    }

    return 0;
}

```
## 2. 창의적인 풀이 
해당 간선을 포함하는지만 확인하면 되는 것이기 때문에 모든 간선의 가중치에 2를 곱해 짝수로 만들고, g-h 간선의 가중치만 1을 빼 홀수로 만든다.  
그리고 S -> D의 최단 경로의 길이가 홀수이면 g-h 간선을 포함하기 때문에 이 목적지를 후보에 올리면 된다.  
이 방법은 특정한 정점으로 부터 다른 정점까지의 거리를 구하는 작업을 한번만 하면 되기 때문에 속도에 이점이 있다. 
```c++
void readData()
{
    int m,t,g,h;
    cin>>vertexNum>>m>>t;
    cin>>start>>g>>h;
    for(int i=0;i<m;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        // g-h 간선만 홀수로 만든다.
        c*=2;
        if((a==g && b==h) || (a==h && b==g))
            c-=1;
        adj[a].push_back(make_pair(b,c));
        adj[b].push_back(make_pair(a,c));
        
    }
    for(int i=0;i<t;++i)
    {
        int a; cin>>a;
        destination.push_back(a);
    }
}

vector<int> getDist(int src)
{
    vector<int> dist(vertexNum+1, INF);
    dist[src]=0;
    priority_queue<pair<int,int> > pq;
    pq.push(make_pair(0,src));
    while(!pq.empty())
    {
        int cost= -pq.top().first;
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

void clearData()
{
    for(int i=0;i<vertexNum+1;++i)
        adj[i].clear();
    destination.clear();
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        readData();
        vector<int> dist=getDist(start);
        
        sort(destination.begin(),destination.end());
        for(int i=0;i<destination.size();++i)
        {
            int cost=dist[destination[i]];
            if(cost!=INF && cost%2==1)
                cout<<destination[i]<<' ';
        }
        
        cout<<endl;
        clearData();
    }

    return 0;
}
```
