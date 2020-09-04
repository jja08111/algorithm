# 해결 
너비 우선 탐색을 이용한 네트워크 유량 알고리즘을 통한 해결과 이분 매칭을 이용한 해결 2가지 방법을 이용해봤다.     

## 1. 에드몬드-카프(Edmonds-Karp) 알고리즘을 통한 해결 
### 그래프 모델링 
각 정점을 소스, 할 수 있는 일의 양, 직원, 일(작업), 싱크로 구분하여 설정했다.  

기존에 할당된 일을 처리한 후에 벌점으로 해야 하는 일을 계산할 때에 유량 전체를 0으로 다시 초기화 하지 않고 변경되는 용량과 유량만 초기화하였다.  
변경되는 부분은 소스에서 할 수 있는 일의 양으로 가는 간선의 용량인데, 초기에는 직원의 수 만큼 설정했다가 이후에는 벌점의 크기로 변경했다.  
변경 시 이미 유량을 흘려 보냈으므로 유량을 0으로 초기화 해주었다.  
그리고 각 직원은 자신의 벌점이 얼마인지 모르기 때문에 최대 많은 일을 할 수 있도록 용량을 설정했다.  

### 구현 
기본으로 해야 하는 일과 벌점으로 하는 일의 양을 더하면 결과가 나온다.  
```c++
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAX=2010;
const int INF=987654321;

int V,N,K;
int capacity[MAX][MAX], flow[MAX][MAX];

void makeGraph()
{
    int m;
    cin>>N>>m>>K;
    
    V=3+N+m;
    
    // 소스에서 할 수 있는 일의 양으로(초기 값: 현재 직원 수)
    capacity[0][1]=N;
    
    for(int i=0;i<N;++i)
    {
        int canDoNum;
        cin>>canDoNum;
        // 할 수 있는 일의 양에서 직원으로(초기 값: 1)
        capacity[1][3+i]=1;
        for(int j=0;j<canDoNum;++j)
        {
            int toDo;
            cin>>toDo;
            --toDo;
            // 직원에서 일로
            capacity[3+i][3+N+toDo]=1;
        }
    }
    // 일에서 싱크로
    for(int i=0;i<m;++i)
        capacity[3+N+i][2]=1;
}

int networkFlow(int source, int sink)
{
    int totalFlow=0;
    // 증가 경로가 없을 때 까지 반복한다.
    while(true)
    {
        // 증가 경로를 찾는다. 
        vector<int> parent(V,-1);
        queue<int> q;
        parent[0]=0;
        q.push(0);
        while(!q.empty() && parent[sink]==-1)
        {
            int here=q.front(); q.pop();
            for(int there=0;there<V;++there)
                if(parent[there]==-1 && capacity[here][there]-flow[here][there]>0)
                {
                    parent[there]=here;
                    q.push(there);
                }
        }
        // 증가 경로가 없으면 종료한다.
        if(parent[sink]==-1)
            break;
        // 증가 경로에서 유량을 결정한다.  
        int amount=INF;
        for(int p=sink;p!=source;p=parent[p])
            amount=min(amount,capacity[parent[p]][p]-flow[parent[p]][p]);
        // 증가 경로에서 유량을 흘려 보낸다.
        for(int p=sink;p!=source;p=parent[p])
        {
            flow[parent[p]][p]+=amount;
            flow[p][parent[p]]-=amount;
        }
        totalFlow+=amount;
    }
    return totalFlow;
}

int getMaxNum()
{
    memset(flow,0,sizeof(flow));
    int basicWork=networkFlow(0,2);
    
    // 벌점만큼 추가로 일을 부여한다.
    capacity[0][1]=K;
    flow[0][1]=0;
    // 각 직원은 자신의 벌점이 얼마인지 모른다.
    for(int i=0;i<N;++i)
        capacity[1][3+i]=N+K;
    
    return basicWork+networkFlow(0,2);
}

int main()
{
    makeGraph();
    
    int ret=getMaxNum();
    cout<<ret<<endl;
    return 0;
}

```
--------
## 2. 이분 매칭을 이용한 해결 
그룹 A와 그룹 B로 나뉜 네트워크에서 포드-풀커슨 알고리즘을 응용해 증가 경로를 찾은 뒤 유량을 보내는 것을 반복한다.  
유량을 보내는 것은 A에 속한 a정점과 B에 속한 b정점을 매치하는 것으로 표현한다.  
이 문제에서는 직원들에게 일을 매칭시키는 것으로 이해할 수 있다.  

그렇다면 벌점은 어떻게 처리해야 하는가?  
하나의 방법은 각 직원마다 증가 경로가 더이상 존재하지 않을 때 까지 증가 경로가 있는지 찾아 보며, 증가 경로가 존재하면 매칭시키고 결과 값을 증가시키는 것이다.  

이와 같은 방법으로 구현한 1번보다 간단한 코드는 아래와 같으며, 이 방법은 1번 방법보다 공간 복잡도를 9배 줄일 수 있다.  
```c++
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAX=1001;
const int INF=987654321;

int n,m,k;
vector<int> adj[MAX];
vector<int> bMatch;
vector<bool> visited;

void makeGraph()
{
    cin>>n>>m>>k;
    for(int i=0;i<MAX;++i)
        adj[i].clear();
    for(int person=0;person<n;++person)
    {
        int canDoNum;
        cin>>canDoNum;
        for(int j=0;j<canDoNum;++j)
        {
            int todo;
            cin>>todo;
            --todo;
            adj[person].push_back(todo);
        }
    }
}

bool dfs(int a)
{
    if(visited[a])
        return false;
    visited[a]=true;
    for(int i=0;i<adj[a].size();++i)
    {
        int b=adj[a][i];
        if(bMatch[b]==-1 || dfs(bMatch[b]))
        {
            bMatch[b]=a;
            return true;
        }
    }
    return false;
}

int getMaxNum()
{
    bMatch=vector<int>(m,-1);
    int size=0;
    for(int start=0;start<n;++start)
    {
        visited=vector<bool>(n,false);
        if(dfs(start))
            ++size;
    }
    for(int start=0;start<n;++start)
    {
        while(k)
        {
            visited=vector<bool>(n,false);
            if(!dfs(start))
                break;
            ++size;
            --k;
        }
    }
    return size;
}

int main()
{
    makeGraph();
    
    cout<<getMaxNum()<<endl;
    return 0;
}
```
