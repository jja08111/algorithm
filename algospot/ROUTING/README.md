# 해결 
간선에 가중치가 있으니 다익스트라 알고리즘을 이용하여 해결할 수 있다.  

책에는 "c는 언제나 1 이상 3 이하의 실수입니다." 라고 되어있으나 온라인 문제에는 "1 이상의 실수" 라고 되어있어 범위를 벗어난다.  
이 때문에 이미 방문하지 않은 정점을 방문했을 때 계산한 값이 무한대를 넘어버려 계속 오류가 나는 듯 하다.  

그래서 방문하지 않은 정점의 거리를 -1로 저장하여 따로 처리하니 통과하였다.  
풀고도 찝찝한 문제였다.  
```c++
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

const int MAX_V=10000;

vector<pair<int,double> > adj[MAX_V];

double getMinNoise(int V)
{
    vector<double> dist(V,-1);
    dist[0]=1.0;
    priority_queue<pair<double,int> > pq;
    pq.push(make_pair(-1.0,0));
    
    while(!pq.empty())
    {
        double cost=-pq.top().first;
        int here=pq.top().second;
        pq.pop();
        
        if(dist[here]<cost)
            continue;
        
        for(int i=0;i<adj[here].size();++i)
        {
            int there=adj[here][i].first;
            double nextDist=cost*adj[here][i].second;
            if(dist[there]==-1 || nextDist<dist[there])
            {
                dist[there]=nextDist;
                pq.push(make_pair(-nextDist,there));
            }
        }
    }
    return dist[V-1];
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int n,m;
        cin>>n>>m;
        
        for(int i=0;i<m;++i)
        {
            int u,v;
            double w;
            cin>>u>>v>>w;
            adj[u].push_back(make_pair(v,w));
            adj[v].push_back(make_pair(u,w));
        }
        printf("%.10f \n",getMinNoise(n));
        
        for(int i=0;i<n;++i)
            adj[i].clear();
    }

    return 0;
}
```
# 참고 
http://joonas-yoon.blogspot.com/2016/05/routing.html
