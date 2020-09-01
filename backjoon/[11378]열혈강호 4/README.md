# 해결 
네트워크 유량에서 이분 매칭으로 푸는 것이 정석이나 (더 느리지만)너비 우선 탐색을 활용한 네트워크 유량 알고리즘을 이용하여 해결 했다.     

### 그래프 모델링 
각 정점을 소스, 할 수 있는 일의 양, 직원, 일(작업), 싱크로 구분하여 설정했다.  

유량 전체를 0으로 다시 초기화 하지 않고 변경되는 용량과 유량만 초기화하였다.  
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
