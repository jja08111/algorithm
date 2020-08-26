# 해결 
시작 정점과 도착 정점이 여러개 주어지니 플로이드 알고리즘을 이용하여 해결하는 문제이다.  

하지만 이 문제는 일반적인 상황과는 다르게 **최단경로 내의 정점 값이 가장 큰 값과 경로값의 합이 최소화** 되는 값을 찾아야 한다.  

이는 **인접 행렬 W를 추가로 더 선언**하여서 한 곳에는 **단속에 걸리는 시간값 delay가 없는 최단 시간 값**들을, 다른 한 곳에는 **delay를 포함한 최단 시간**을 저장하여 해결할 수 있다.  
이렇게 구분하여 저장하는 이유는 새로 집합에 추가된 경유지 w가 있을 때 이 경유지를 경유하는 것이 더 빠른 경로인지 비교하는데 쓰이기 때문이다.  
즉, adj만을 이용하여 계산하면 delay가 하나가 아니라 여러개 계속해서 포함되기 때문이다.  

그리고 최악의 경우를 고려하는 문제이기 때문에 **각 정점을 단속에 걸리는 시간 별로 정렬**하여, **시간이 적게 걸리는 정점부터 경유지 집합에 추가**해 나가면 된다.  

이러한 변형이 가능한 이유는 **플로이드 알고리즘이 경유지 집합에 정점을 하나씩 추가하는 순서**가 알고리즘 정당성에 **영향을 주지 않기 때문**이다.  
```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF=987654321;
const int MAX_V=501;

int V;
int adj[MAX_V][MAX_V];
int W[MAX_V][MAX_V];
int delay[MAX_V];

void makeGraph()
{
    int E;
    cin>>V>>E;
    
    for(int i=0;i<V;++i)
        cin>>delay[i];
    
    for(int i=0;i<V;++i)
        for(int j=0;j<V;++j)
        {
            adj[i][j]=INF;
            W[i][j]=INF;
        }
    
    for(int i=0;i<E;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        --a; --b;
        adj[a][b]=c;
        adj[b][a]=c;
        W[a][b]=c;
        W[b][a]=c;
    }
}

void floyd()
{
    vector<pair<int,int> > order;
    for(int i=0;i<V;++i)
    {
        adj[i][i]=0;
        W[i][i]=0;
        order.push_back(make_pair(delay[i],i));
    }
    sort(order.begin(),order.end());
    for(int k=0;k<V;++k)
    {
        int w=order[k].second;
        for(int i=0;i<V;++i)
            for(int j=0;j<V;++j)
            {
                adj[i][j]=min(adj[i][j],adj[i][w]+adj[w][j]);
                W[i][j]=min(W[i][j],adj[i][w]+delay[w]+adj[w][j]);
            }
    }
}

int main()
{
    makeGraph();
    floyd();
    
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int s,t;
        cin>>s>>t;
        --s; --t;
        
        cout<<W[s][t]<<endl;
    }
    
    return 0;
}
```
