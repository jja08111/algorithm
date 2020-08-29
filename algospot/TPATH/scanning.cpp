#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX_V=2001;
const int INF=987654321;

int V,E;
vector<pair<int,int> > adj[MAX_V];
vector<int> weights;

bool hasPath(int lo, int hi)
{
    vector<bool> discoverd(V,false);
    queue<int> q;
    discoverd[0]=true;
    q.push(0);
    while(!q.empty())
    {
        int here=q.front();
        q.pop();
        for(int i=0;i<adj[here].size();++i)
        {
            int there=adj[here][i].first;
            int cost=adj[here][i].second;
            if(!discoverd[there] && lo<=cost && cost<=hi)
            {
                if(there==V-1)
                    return true;
                discoverd[there]=true;
                q.push(there);
            }
        }
    }
    return false;
}

int scanning() 
{
    int lo=0, hi=0, ret=INF;
    while(lo<weights.size() && hi<weights.size())
    {
        if(hasPath(weights[lo],weights[hi]))
        {
            ret=min(ret,weights[hi]-weights[lo]);
            ++lo;
        }
        else
            ++hi;
    }
    return ret;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>V>>E;
        for(int i=0;i<E;++i)
        {
            int a,b,c;
            cin>>a>>b>>c;
            
            adj[a].push_back(make_pair(b,c));
            adj[b].push_back(make_pair(a,c));
            
            weights.push_back(c);
        }
        sort(weights.begin(),weights.end());
        
        cout<<scanning()<<endl;
        
        for(int i=0;i<V;++i)
            adj[i].clear();
        weights.clear();
    }
    return 0;
}
