#include <iostream>
#include <vector>
#include <utility>
#include <set>
using namespace std;

const int MAX=100001;

// adj[here]=(there,dist)
vector<pair<int,int> > adj[MAX];
bool visited[MAX];
// 잎과 잎 사이의 거리 중 가장 긴 값
int longest=0;

int getDiameter(int here)
{
    visited[here]=true;
    
    set<int> heights;
    for(int i=0;i<adj[here].size();++i)
    {
        int cand=adj[here][i].first;
        int dist=adj[here][i].second;
        if(!visited[cand])
        {
            heights.insert(dist+getDiameter(cand));
        }
    }
    
    if(heights.empty())
        return 0;
        
    set<int>::iterator it=heights.end();
    int back = *(--it);
    if(heights.size()>=2)
    {
        int back2 = *(--it);
        longest=max(longest,back+back2);
    }
    return back;
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
    
    //잎-잎 거리와 루트-잎 거리 중 더 큰 값을 출력
    int h=getDiameter(1);
    int ret=max(h,longest);
    cout<<ret;
    
    return 0;
}
