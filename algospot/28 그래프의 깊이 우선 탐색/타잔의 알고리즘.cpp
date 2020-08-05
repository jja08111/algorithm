#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<int> > adj;
vector<int> sccId;
vector<int> discovered;
stack<int> st;
int sccCounter, vertexCounter;

int scc(int here)
{
    int ret=discovered[here]=vertexCounter++;
    st.push(here);
    for(int i=0;i<adj[here].size();++i)
    {
        int there=adj[here][i];
        // (here, there)가 트리 간선
        if(discovered[there]==-1)
            ret=min(ret,scc(there));
        // there가 무시해야 하는 교차 간선이 아니라면
        else if(sccId[there]==-1)
            ret=min(ret,discovered[there]);
    }
    
    // here에서 부모로 올라가는 간선을 끊어야 할지 확인한다.
    if(ret==discovered[here])
    {
        while(true)
        {
            int t=st.top();
            st.pop();
            sccId[t]=sccCounter;
            if(t==here)
                break;
        }
        sccCounter++;
    }
    return ret;
}

vector<int> tarjanSCC()
{
    sccId=discovered=vector<int>(adj.size(), -1);
    sccCounter=vertexCounter=0;
    for(int i=0;i<adj.size();++i)
        if(discovered[i]==-1)
            scc(i);
    return sccId;
}
