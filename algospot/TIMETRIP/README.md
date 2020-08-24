# 해결 
밸만 포드만 알고리즘을 이용하여 간선의 가중치 중 음수가 있는 그래프의 특정 경로의 최대값, 최소값을 찾는 문제이다.  

이 문제에서 최대값을 구하는 것은 간선의 값에 음수를 씌워 해결할 수 있다. 물론 출력시 결과값에 음수를 씌워야 한다.  

주의할 점은 기존 알고리즘은 음수 사이클이 존재하기만 하면 빈 벡터를 반환하여 표시했으나, 
문제에서는 음수 사이클이 그저 존재하는 것이 아니라 해당 경로 내에서 음수 사이클이 있는지 확인해야 하는 것이다.  

이를 구현하는 방법은 먼저 reachable이라는 bool형 배열을 이용하여 그래프 생성시 경로가 존재하는지를 저장한다.  
그리고 V번째 완화 과정에서 어떠한 정점이 완화 되었고, 그 정점이 START에서 END로 가는 최단경로에 있을 경우 이 경로에 음수 사이클이 존재하는 것이다.  
이러한 때에 경로가 끊어진 경우를 표현하는 값이 INF보다 약간 작은 수 이니 아주 작은 값을 반환한다.  

경로가 끊어진 경우 dist[END]의 값을 INF-M보다 큰 수로 비교하는 이유는 시작 정점에서 중간지점으로 가는 경로가 없고 중간지점에서 도착 정점이 음수 사이클인 경우 
도착지점의 값이 INF보다 작아지기 때문이다.  

```c++
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAX_V=101;
const int INF=987654321;
const int M=98765432;

enum { START=0, END };

int V,E;
vector<pair<int,int> > adj[MAX_V];
// reachable[a][b]: a정점에서 b정점으로 도달 가능여부
bool reachable[MAX_V][MAX_V];

void makeGraph()
{
    cin>>V>>E;
    memset(reachable,false,sizeof(reachable));
    for(int i=0;i<E;++i)
        {
            int a,b,c;
            cin>>a>>b>>c;
            adj[a].push_back(make_pair(b,c));
            reachable[a][b]=true;
        }
    
    for(int i=0;i<V;++i)
        reachable[i][i]=true;
    
    for(int k=0;k<V;++k)
        for(int i=0;i<V;++i)
            for(int j=0;j<V;++j)
                // 중간 지점을 통해 연결된 경우가 있으면 추가한다.
                reachable[i][j]|=reachable[i][k]&&reachable[k][j];
}

int getMaxTime(int delta)
{
    vector<int> upper(V,INF);
    upper[START]=0;
    for(int it=0;it<V-1;++it)
        for(int here=0;here<V;++here)
            if(upper[here]<INF)
            {
                for(int i=0;i<adj[here].size();++i)
                {
                    int there=adj[here][i].first;
                    int cost=adj[here][i].second*delta;
                    upper[there]=min(upper[there],cost+upper[here]);
                }
            }
    
    for(int here=0;here<V;++here)
        for(int i=0;i<adj[here].size();i++)
        {
            int there=adj[here][i].first;
            int cost=adj[here][i].second*delta;
            if(upper[there]>cost+upper[here])
                // 정점이 완화되었는데 START에서 END로 가는 경로에 있을 경우
                if(reachable[START][here] && reachable[here][END])
                    return -INF;
        }
    
    return upper[END];
}

void printRet(const int past, const int present)
{
    if(past== -INF)
        cout<<"INFINITY"<<" ";
    else
        cout<<past<<" ";
    
    if(present== -INF)
        cout<<"INFINITY"<<endl;
    else
        cout<<-present<<endl;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        makeGraph();
        
        int past=getMaxTime(1);
        
        if(past>=INF-M)
        {
            cout<<"UNREACHABLE"<<endl;
            continue;
        }
        
        int present=getMaxTime(-1);
        
        printRet(past,present); 
        
        for(int i=0;i<V;++i)
            adj[i].clear();
    }
    return 0;
}

```
