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

bool canMakeList()
{
    int n=adj.size();
    
    makeSCCs();
    
    for(int i=0;i<n;i+=2)
        if(sccId[i]==sccId[i+1])
            return false;
    
    vector<pair<int,int> > order;
    for(int i=0;i<n;++i)
        order.push_back(make_pair(-sccId[i],i));
    sort(order.begin(),order.end());
    
    for(int i=0;i<n;++i)
    {
        int vertex=order[i].second;
        int variable=vertex/2;
        bool isTrue=(vertex%2==0);
        if(variable==0)
            return !isTrue;
    }
}

int main()
{
    int n,m;
    while(scanf("%d %d",&n,&m)!=-1)
    {
        adj.clear(); adj.resize(n*2);
        
        for(int i=0;i<m;++i)
        {
            int a,b;
            cin>>a>>b;
            a=convert(a);
            b=convert(b);
            adj[a^1].push_back(b); // !a -> b
            adj[b^1].push_back(a); // !b -> a
        }
        
        if(canMakeList())
            cout<<"yes"<<endl;
        else
            cout<<"no"<<endl;
    }

    return 0;
}
