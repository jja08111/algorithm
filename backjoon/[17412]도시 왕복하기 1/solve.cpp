#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_V=401;
const int INF=987654321;

int V;
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];

int getMaxFlow(int source, int sink)
{
    int ret=0;
    while(true)
    {
        // 너비 우선 탐색으로 증가 경로를 찾는다.
        vector<int> parent(V,-1);
        queue<int> q;
        parent[source]=source;
        q.push(source);
        while(!q.empty() && parent[sink]==-1)
        {
            int here=q.front(); q.pop();
            for(int there=0;there<V;++there)
                if(parent[there]==-1 && capacity[here][there]-flow[here][there]>0)
                {
                    q.push(there);
                    parent[there]=here;
                }
        }
        
        // 증가 경로가 없으면 종료한다.
        if(parent[sink]==-1) break;
        
        // 증가 경로를 통해 유량을 얼마나 보낼지 결정한다.
        int amount=INF;
        for(int p=sink;p!=source;p=parent[p])
            amount=min(amount,capacity[parent[p]][p]-flow[parent[p]][p]);
        
        // 증가 경로를 통해 유량을 보낸다.
        ret+=amount;
        for(int p=sink;p!=source;p=parent[p])
        {
            flow[parent[p]][p]+=amount;
            flow[p][parent[p]]-=amount;
        }
    }
    return ret;
}

int main()
{
    int E;
    cin>>V>>E;
    
    for(int i=0;i<V;++i)
        for(int j=0;j<V;++j)
            capacity[i][j]=flow[i][j]=0;
    
    for(int i=0;i<E;++i)
    {
        int a,b;
        cin>>a>>b;
        --a;--b;
        ++capacity[a][b];
    }
    
    cout<<getMaxFlow(0,1)<<endl;

    return 0;
}
