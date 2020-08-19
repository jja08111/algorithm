#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

const int MAX_V=10000;

vector<pair<int,double> > adj[MAX_V];

double getMinNoise(int V)
{
    vector<double> dist(V,-1);
    dist[0]=1.0;
    priority_queue<pair<double,int> > pq;
    pq.push(make_pair(-1.0,0));
    
    while(!pq.empty())
    {
        double cost=-pq.top().first;
        int here=pq.top().second;
        pq.pop();
        
        if(dist[here]<cost)
            continue;
        
        for(int i=0;i<adj[here].size();++i)
        {
            int there=adj[here][i].first;
            double nextDist=cost*adj[here][i].second;
            if(dist[there]==-1 || nextDist<dist[there])
            {
                dist[there]=nextDist;
                pq.push(make_pair(-nextDist,there));
            }
        }
    }
    return dist[V-1];
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int n,m;
        cin>>n>>m;
        
        for(int i=0;i<m;++i)
        {
            int u,v;
            double w;
            cin>>u>>v>>w;
            adj[u].push_back(make_pair(v,w));
            adj[v].push_back(make_pair(u,w));
        }
        printf("%.10f \n",getMinNoise(n));
        
        for(int i=0;i<n;++i)
            adj[i].clear();
    }

    return 0;
}
