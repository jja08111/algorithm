#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF=987654321;
const int MAX_V=801;

int V,E;
vector<pair<int,int> > adj[MAX_V];

int getMinRoute(int src, int end)
{
    vector<int> dist(V+1,INF);
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
    return dist[end];
}

int main()
{
    cin>>V>>E;
    for(int i=0;i<E;++i)
    {
        int u,v,c;
        cin>>u>>v>>c;
        adj[u].push_back(make_pair(v,c));
        adj[v].push_back(make_pair(u,c));
    }
    int via1, via2;
    cin>>via1>>via2;
    
    int middle=getMinRoute(via1,via2);
    int ret=getMinRoute(1,via1)+middle+getMinRoute(via2,V);
    ret=min(ret,getMinRoute(1,via2)+middle+getMinRoute(via1,V));
    
    if(ret<0 || INF<=ret)
        cout<<-1<<endl;
    else
        cout<<ret<<endl;
    return 0;
}
