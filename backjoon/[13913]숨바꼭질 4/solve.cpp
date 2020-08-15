#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAX=100000;

int n,k;

// 다음 정점의 값 반환 
int nextVertex(const int here, const int select)
{
    switch(select)
    {
    case 0:
        if(2*here<=MAX)
            return here*2;
        break;
    case 1:
        if(here-1>=0)
            return here-1;
        break;
    case 2:
        if(here+1<=MAX)
            return here+1;
        break;
    }
    return -1;
}

vector<int> bfs()
{
    vector<int> parent(MAX+1,-1);
    queue<int> q;
    q.push(n);
    parent[n]=n;
    while(!q.empty())
    {
        int here=q.front();
        q.pop();
        
        // 목표하는 위치에 도달하면 종료
        if(here==k)
            return parent;
        
        for(int i=0;i<3;++i)
        {
            int there=nextVertex(here,i);
            if(there==-1)
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
    
    // 목표 위치에서 부모를 따라가며 경로 생성
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
