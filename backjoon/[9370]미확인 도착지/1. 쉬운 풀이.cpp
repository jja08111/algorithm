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
