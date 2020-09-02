#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <numeric>
using namespace std;

const int MAX_NM=101;
const int MAX_V=100+100+10;
const int INF=987654321;

int V,n,m;
int profit[MAX_NM], cost[MAX_NM], requires[MAX_NM][MAX_NM];
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];

int networkFlow(int source, int sink)
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
        for(int p=sink;p!=source;p=parent[p])
        {
            flow[parent[p]][p]+=amount;
            flow[p][parent[p]]-=amount;
        }
        ret+=amount;
    }
    return ret;
}

int maxProfit()
{
    // 네트워크를 만든다.
    const int SRC=0, SNK=1;
    V=n+m+2;
    memset(capacity,0,sizeof(capacity));
    memset(flow,0,sizeof(flow));
    for(int i=0;i<n;++i)
        capacity[SRC][2+i]=profit[i];
    for(int i=0;i<m;++i)
        capacity[2+n+i][SNK]=cost[i];
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            if(requires[i][j])
                capacity[2+i][2+n+j]=INF;
    // 모든 사업의 수익의 합을 구한다.  
    int M=accumulate(profit,profit+n,0);
    int C=networkFlow(SRC,SNK);
    return M-C;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>n>>m;
        for(int i=0;i<n;++i)
            cin>>profit[i];
        for(int i=0;i<m;++i)
            cin>>cost[i];
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
                cin>>requires[i][j];
        
        cout<<maxProfit()<<endl;
    }
    return 0;
}
