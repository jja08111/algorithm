#include <iostream>
#include <vector>
#include <utility>
#include <cstring>
using namespace std;

const int MAX=100001;

// adj[here]=(there,dist)
vector<pair<int,int> > adj[MAX];
bool visited[MAX];
int longest, farthestNode;

void getDiameter(int here, int dist)
{
    if(visited[here])
        return;
    
    visited[here]=true;
    if(longest<dist)
    {
        longest=dist;
        farthestNode=here;
    }
    
    for(int i=0;i<adj[here].size();++i)
    {
        int there=adj[here][i].first;
        int candDist=adj[here][i].second;
        getDiameter(there,candDist+dist);
    }
}

int main()
{
    int n;
    cin>>n;
    
    for(int i=0;i<n;++i)
    {
        int here;
        cin>>here;
        while(true)
        {
            int there, dist;
            
            scanf("%d",&there);
            if(there==-1) 
                break;
            scanf("%d",&dist);
            
            adj[here].push_back(make_pair(there,dist));
        }
    }
    // 루트에서 가장 먼 정점을 찾음
    longest=0;
    getDiameter(1,0);
    
    // 루트에서 가장 먼 정점과 가장 멀리 떨어진 정점과의 거리를 구한다.
    longest=0;
    memset(visited,false,sizeof(visited));
    getDiameter(farthestNode,0);
    cout<<longest;
    
    return 0;
}
