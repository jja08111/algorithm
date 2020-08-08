 # 해결 
 도미노는 한 블록을 쓰러트릴 때 같은 SCC내에 있는 블록은 모두 쓰러진다.  
 SCC는 강한 연결 요소인데 이는 방향 그래프에서 두 정점이 모두 각각의 정점으로 향하는 루트가 있는 정점들의 최대 집합들을 모은 것이다.  
 
 ## Solve 1.
 전체 그래프를 SCC로 구분한뒤 각 SCC내의 대표 정점을 하나씩 저장하여 그래프를 압축한다.  
 dfs함수가 종료하는 순간에 새로운 scc가 생성되는데 이러한 특성 때문에 역순의 위상 정렬된 결과를 얻을 수 있다.  
 이러한 sccVertex를 역순으로 이용해 그래프를 dfs하여 최소 개수를 구할 수 있다.  
 ```c++
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
 ```
 ### Solve2.
 다른 방법으로는 생성된 SCC를 이용하여 압축된 scc그래프의 indegree를 구하여 해결하는 방법이 있다.  
 SCC를 형성한 후 간선 a->b 에서 a와 b의 scc id가 다르다면 b의 indegree를 하나 늘리는 방식이다.  
 ```c++
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
 ```
