#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX_V=2+200+20;
const int INF=987654321;

int V;
int n,m;
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
int wins[20], match[200][2];

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

bool canWinWith(int totalWins)
{
    // 이미 totalWins승 이상 한 선수가 있으면 안된다. 
    if(*max_element(wins+1, wins+n)>=totalWins)
        return false;
    // 0번은 소스, 1번은 싱크로 설정
    V=2+m+n;
    memset(capacity,0,sizeof(capacity));
    for(int i=0;i<m;++i)
    {
        // 소스에서 각 경기로 가는 간선
        capacity[0][2+i]=1;
        // 각 경기에서 선수로 가는 간선
        for(int j=0;j<2;++j)
            capacity[2+i][2+m+match[i][j]]=1;
    }
    // 각 선수에서 싱크로, 가능한 최대 승수를 용량으로 하는 간선을 추가
    for(int i=0;i<n;++i)
    {
        int maxWin=(i==0 ? totalWins : totalWins-1);
        capacity[2+m+i][1]=maxWin-wins[i];
    }
    return networkFlow(0,1)==m;
}

int getMinWins()
{
    memset(flow,0,sizeof(flow));
    for(int i=wins[0];i<=m+wins[0];++i)
        if(canWinWith(i))
            return i;
    return -1;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>n>>m;
        
        for(int i=0;i<n;++i)
            cin>>wins[i];
        for(int i=0;i<m;++i)
        {
            int a,b;
            cin>>a>>b;
            match[i][0]=a;
            match[i][1]=b;
        }
        
        cout<<getMinWins()<<endl;        
    }
    return 0;
}
