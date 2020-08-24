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
