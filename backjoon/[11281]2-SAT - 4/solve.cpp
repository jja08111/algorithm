#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

vector<vector<int> > adj;
vector<int> discovered, sccId;
stack<int> st;
int sccCounter, vertexCounter;

inline int convert(int n)
{
    if(n>0)
        return 2*(n-1);
    return -2*(n+1)+1;
}

int dfs(int here)
{
    int ret=discovered[here]=vertexCounter++;
    st.push(here);
    for(int i=0;i<adj[here].size();++i)
    {
        int there=adj[here][i];
        if(discovered[there]==-1)
            ret=min(ret,dfs(there));
        else if(sccId[there]==-1)
            ret=min(ret,discovered[there]);
    }
    if(ret==discovered[here])
    {
        while(true)
        {
            int t=st.top();
            st.pop();
            sccId[t]=sccCounter;
            if(t==here) break;
        }
        sccCounter++;
    }
    return ret;
}

void makeSCCs()
{
    discovered=sccId=vector<int>(adj.size(),-1);
    sccCounter=vertexCounter=0;
    for(int i=0;i<adj.size();++i)
        if(discovered[i]==-1)
            dfs(i);
}

vector<int> solve2SAT()
{
    int n=adj.size();
    makeSCCs();
    // 해를 구할 수 없는 경우 
    for(int i=0;i<n;i+=2)
        if(sccId[i]==sccId[i+1])
            return vector<int>();
    
    // scc가 위상정렬의 역순으로 번호가 배정된 점을 이용한다.
    vector<pair<int,int> > order;
    for(int i=0;i<n;++i)
        order.push_back(make_pair(-sccId[i],i));
    sort(order.begin(), order.end());
    
    vector<int> value(n,-1);
    for(int i=0;i<n;++i)
    {
        int vertex=order[i].second;
        int variable=vertex/2, isTrue=vertex%2==0;
        if(value[variable]!=-1)
            continue;
        value[variable]=!isTrue;
    }
    return value;
}

int main()
{
    int n,m;
    cin>>n>>m;
    
    adj.clear(); adj.resize(2*n);
    
    for(int i=0;i<m;++i)
    {
        int u,v;
        cin>>u>>v;
        u=convert(u);
        v=convert(v);
        adj[u^1].push_back(v); // !u -> v
        adj[v^1].push_back(u); // !v -> u
    }
    
    vector<int> ret=solve2SAT();
    if(ret.empty())
        cout<<0<<endl;
    else
    {
        cout<<1<<endl;
        for(int i=0;i<n;++i)
            cout<<ret[i]<<' ';
    }
    return 0;
}
