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
