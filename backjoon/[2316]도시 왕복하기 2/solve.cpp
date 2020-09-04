#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

enum { SRC, SNK };

const int INF=987654321;
const int MAX_V=810;

int V,E;
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];

int networkFlow(int source, int sink)
{
    int totalFlow=0;
    memset(flow,0,sizeof(flow));
    while(true)
    {
        // 증가 경로를 찾는다. 
        queue<int> q;
        vector<int> parent(V,-1);
        q.push(source);
        parent[source]=source;
        while(!q.empty() && parent[sink]==-1)
        {
            int here=q.front(); q.pop();
            for(int there=0;there<V;++there)
                if(parent[there]==-1 && capacity[here][there]-flow[here][there]>0)
                {
                    parent[there]=here;
                    q.push(there);
                }
        }
        // 더 이상 증가 경로가 없는 경우
        if(parent[sink]==-1)
            break;
        // 증가 경로에 유량을 흘려 보낸다.
        for(int p=sink;p!=source;p=parent[p])
        {
            flow[parent[p]][p]+=1;
            flow[p][parent[p]]-=1;
        }
        totalFlow+=1;
    }
    return totalFlow;
}

int main()
{
    cin>>V>>E;
    V*=2;
    memset(capacity,0,sizeof(capacity));
    // 각 정점을 2개로 분리하고 나뉜 정점 사이 간선(in->out)의 용량을 1로 설정한다.
    for(int i=0;i<V;i+=2)
        capacity[i][i+1]=1;
    // 1번과 2번 정점은 계속 방문 할 수 있다.
    capacity[0][1]=capacity[2][3]=INF;
    
    for(int i=0;i<E;++i)
    {
        int a,b;
        cin>>a>>b;
        --a;--b;
        // 양방향 간선이다.  
        // out -> in 으로 향해야 한다.
        capacity[2*a+1][2*b]=1;
        capacity[2*b+1][2*a]=1;
    }
    
    cout<<networkFlow(SRC*2,SNK*2+1)<<endl;
    return 0;
}
