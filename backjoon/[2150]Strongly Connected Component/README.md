# 해결 
tarjan의 SCC를 생성하는 알고리즘을 이용하여 해결했다.  

위 알고리즘에서 결과의 출력을 위해서 별도의 SCC 이차원 벡터를 선언했다.  
주의할 부분은 정점의 번호가 1번부터 시작하니 실수로 0번 정점에 접근하지 않아야 하는 것이다.  
```c++
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

vector<vector<int> > adj, SCC;
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
        vector<int> setId;
        while(true)
        {
            int t=st.top();
            st.pop();
            sccId[t]=sccCounter;
            
            setId.push_back(t);
            
            if(t==here)
                break;
        }
        sort(setId.begin(), setId.end());
        SCC.push_back(setId);
        sccCounter++;
    }
    return ret;
}

void tarjanSCC()
{
    discovered=sccId=vector<int>(vertexNum+1,-1);
    sccCounter=vertexCounter=0;
    // 정점이 1에서 시작한다.
    for(int i=1;i<adj.size();++i)
        if(discovered[i]==-1)
            dfs(i);
    
    sort(SCC.begin(), SCC.end());
}

int main()
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
    
    cout<<sccCounter<<endl;
    for(int id=0;id<sccCounter;++id)
    {
        for(int i=0;i<SCC[id].size();++i)
            cout<<SCC[id][i]<<' ';
        cout<<-1<<endl;
    }

    return 0;
}
```
