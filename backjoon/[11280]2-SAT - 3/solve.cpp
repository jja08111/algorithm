#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

vector<vector<int> > adj;
vector<int> discovered, sccId;
stack<int> st;
int sccCounter, vertexCounter;

// convert : i = 2t, not i = 2t+1
inline int convertNumToVertex(int n)
{
    if(n>0)
        return (n-1)*2;
    return (-1*n)*2-1;
}

int scc(int here)
{
    int ret=discovered[here]=vertexCounter++;
    st.push(here);
    for(int i=0;i<adj[here].size();++i)
    {
        int there=adj[here][i];
        if(discovered[there]==-1)
            ret=min(ret,scc(there));
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

void makeSCC()
{
    discovered=sccId=vector<int>(adj.size(),-1);
    sccCounter=vertexCounter=0;
    for(int i=0;i<adj.size();++i)
        if(discovered[i]==-1)
            scc(i);
}

int canMakeFuncTrue()
{
    for(int i=0;i<adj.size();i+=2)
        if(sccId[i]==sccId[i+1])
            return 0;
    return 1;
}

int main(void)
{
    int n,m;
    cin>>n>>m;
    
    adj.clear(); adj.resize(n<<1);
    
    for(int i=0;i<m;++i)
    {
        int a,b;
        cin>>a>>b;
        a=convertNumToVertex(a);
        b=convertNumToVertex(b);
        
        adj[a^1].push_back(b); // ~a -> b
        adj[b^1].push_back(a); // ~b -> a
    }
    makeSCC();
    cout<<canMakeFuncTrue()<<endl;
    return 0;
}
