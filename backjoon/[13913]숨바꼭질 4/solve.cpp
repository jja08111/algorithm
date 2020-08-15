#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAX=100001;

int n,k;

inline bool inRange(int n)
{
    return 0<=n && n<MAX;
}

int nextVertex(const int here, const int select)
{
    int there;
    switch(select)
    {
    case 0: there=here*2; break;
    case 1: there=here-1; break;
    case 2: there=here+1; break;
    }
    
    if(inRange(there))
        return there;
    return -1;
}

vector<int> bfs()
{
    vector<int> parent(MAX,-1);
    queue<int> q;
    q.push(n);
    parent[n]=n;
    
    while(!q.empty())
    {
        int here=q.front();
        q.pop();
        
        if(here==k)
            return parent;
        
        for(int i=0;i<3;++i)
        {
            int there=nextVertex(here,i);
            if(there<0)
                continue;
            
            if(parent[there]==-1)
            {
                parent[there]=here;
                q.push(there);
            }
        }
    }
}

vector<int> getReverseRoute()
{
    vector<int> parent=bfs();
    vector<int> route;
    
    int here=k;
    while(parent[here]!=here)
    {
        route.push_back(here);
        here=parent[here];
    }
    route.push_back(n);
    
    return route;
}

int main()
{
    cin>>n>>k;
    
    vector<int> ret=getReverseRoute();
    
    cout<<ret.size()-1<<endl;
    for(int i=ret.size()-1;i>=0;--i)
        cout<<ret[i]<<' ';
    
    return 0;
}
