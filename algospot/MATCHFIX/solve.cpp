#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX_V=2+200+20;
const int INF=987654321;

int V;
int n,m,totalFlow;
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
    // 이전에 계산한 Flow를 포함시켜 반환한다.
    return totalFlow+=ret;
}

// 0번 선수가 총 totalWins승으로 우승할 수 있는지 여부를 확인한다.
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
    // 이때 모든 경기에 승자를 지정할 수 있는가?
    return networkFlow(0,1)==m;
}

// 우승할 수 있는 최소한의 총 승리 횟수 반환
int getMinTotalWins(const int maxAddWin)
{
    memset(flow,0,sizeof(flow));
    totalFlow=0;
    for(int i=0;i<=maxAddWin;++i)
        if(canWinWith(i+wins[0]))
            return i+wins[0];
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
        // 0번 선수가 추가로 이길 수 있는 최대 횟수
        int maxAddWin=0;
        for(int i=0;i<m;++i)
        {
            int a,b;
            cin>>a>>b;
            match[i][0]=a;
            match[i][1]=b;
            if(a==0 || b==0)
                ++maxAddWin;
        }
        
        cout<<getMinTotalWins(maxAddWin)<<endl;        
    }
    return 0;
}
