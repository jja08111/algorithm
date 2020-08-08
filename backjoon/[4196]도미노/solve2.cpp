#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<int> > adj;
vector<int> discovered, sccId;
stack<int> st;
int vertexNum, edgeNum, sccCounter, vertexCounter;

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

void getSCC()
{
    discovered=sccId=vector<int>(vertexNum+1, -1);
    sccCounter=vertexCounter=0;
    
    for(int i=1;i<adj.size();++i)
        if(discovered[i]==-1)
            dfs(i);
}

int getMinHittingSize()
{
    vector<int> sccIndegree(sccCounter,0);
    
    for(int here=0;here<adj.size();++here)
        for(int iter=0;iter<adj[here].size();++iter)
        {
            int there=adj[here][iter];
            if(sccId[here]!=sccId[there])
                sccIndegree[sccId[there]]++;
        }
    
    int ret=0;
    for(int i=0;i<sccCounter;++i)
        if(sccIndegree[i]==0)
            ret++;
    
    return ret;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>vertexNum>>edgeNum;
        
        adj=vector<vector<int> >(vertexNum+1);
        
        for(int i=0;i<edgeNum;++i)
        {
            int a,b;
            cin>>a>>b;
            adj[a].push_back(b);
        }
        
        getSCC();
        
        cout<<getMinHittingSize()<<endl;
    }

    return 0;
}
