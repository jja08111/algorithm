#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<int> > adj;
vector<int> discovered, sccId, sccVertex;
stack<int> st;
int vertexNum, edgeNum, sccCounter, vertexCounter;

int tarjanDFS(int here)
{
    int ret=discovered[here]=vertexCounter++;
    st.push(here);
    
    for(int i=0;i<adj[here].size();++i)
    {
        int there=adj[here][i];
        if(discovered[there]==-1)
            ret=min(ret,tarjanDFS(there));
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
            
            if(t==here) 
            {
                sccVertex.push_back(here);
                break;
            }
        }
        sccCounter++;
    }
    
    return ret;
}

void tarjanSCC()
{
    sccVertex.clear();
    discovered=sccId=vector<int>(vertexNum+1, -1);
    sccCounter=vertexCounter=0;
    
    for(int i=1;i<adj.size();++i)
        if(discovered[i]==-1)
            tarjanDFS(i);
}

void dfs(int here)
{
    discovered[here]=1;
    for(int i=0;i<adj[here].size();++i)
    {
        int there=adj[here][i];
        if(discovered[there]==-1)
            dfs(there);
    }
}

int getMinHittingSize()
{
    discovered=vector<int>(vertexNum+1, -1);
    int hitCounter=0;
    
    for(int i=sccCounter-1;i>=0;--i)
        if(discovered[sccVertex[i]]==-1)
        {
            dfs(sccVertex[i]);
            hitCounter++;
        }
    
    return hitCounter;
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
        
        tarjanSCC();
        cout<<getMinHittingSize()<<endl;
    }

    return 0;
}
