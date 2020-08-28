# 해결 
이 문제를 보면 최소 스패닝 트리 알고리즘을 이용하여 해결하는데 어떻게 구현할지 고민하게 된다.   
처음에는 이미 연결된 정점을 압축하여 하나의 정점으로 표현하여 얻은 그래프에서 최소 스패닝 트리를 구할 수 있다고 생각했다.  
하지만 구현하기 쉽지 않을 것 같다.  

## 크루스칼의 알고리즘 
그러다 떠올린 방법은 먼저 크루스칼의 알고리즘을 이용하여 이미 묶인 정점을 DisJointSet에서 같은 집합으로 묶는다.  
그 후 나머지 각 정점들을 모두 돌아가며 간선 목록을 만든 뒤, 거리가 가까운 순서대로 처리하면 된다.  
```c++
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct DisjointSet
{
    vector<int> parent, rank;
    DisjointSet(int n) : parent(n), rank(n,1)
    { 
        for(int i=0;i<n;++i)
            parent[i]=i;
    }
    int find(int u)
    {
        if(u==parent[u]) return u;
        return parent[u]=find(parent[u]);
    }
    void merge(int u, int v)
    {
        u=find(u); v=find(v);
        if(u==v)
            return;
        if(rank[u]>rank[v])
            swap(u,v);
        parent[u]=v;
        if(rank[u]==rank[v])
            ++rank[v];
    }
};

const int MAX_V=501;

int V;
int pos[MAX_V][2];

double kruskal(DisjointSet& sets)
{
  	double ret=0;
    vector<pair<int,pair<int,int> > > edges;
    for(int u=0;u<V;++u)
        for(int v=u+1;v<V;++v)
        {
            if(sets.find(u)==sets.find(v))
            	continue;
            int costSqr=pow(pos[u][0]-pos[v][0],2)+pow(pos[u][1]-pos[v][1],2);
            edges.push_back(make_pair(costSqr,make_pair(u,v)));
        }
    sort(edges.begin(), edges.end());
    
    for(int i=0;i<edges.size();++i)
    {
        int costSqr=edges[i].first;
        int u=edges[i].second.first, v=edges[i].second.second;
        if(sets.find(u)==sets.find(v))
            continue;
        ret+=sqrt(costSqr);
        sets.merge(u,v);
    }
    return ret;
}

int main()
{
    int testCase;
    cin>>testCase;
    
    cout<<fixed;
    cout.precision(10);
    
    while(testCase--)
    {
        int m;
        cin>>V>>m;
        
        for(int i=0;i<2;++i)
            for(int k=0;k<V;++k)
            {   
                int p; cin>>p;
                pos[k][i]=p;
            }
        
        DisjointSet sets(V);
        for(int i=0;i<m;++i)
        {
            int u,v;
            cin>>u>>v;
            sets.merge(u,v);
        }
        
        cout<<kruskal(sets)<<endl;
    }

    return 0;
}
```

## 프림의 알고리즘 
하지만 더 빠른 방법이 있는데 밀집 그래프에 유리한 프림의 알고리즘이다.  
모든 간선을 INF로 초기화 한 뒤 이미 사용된 간선의 가중치는 0으로 초기화 한다.  

그 후 0번 정점부터 시작하여 트리에 추가된 정점은 제외한 정점들을 확인한다.  

만약 다음 정점과의 간선의 가중치가 아직 INF라면 거리를 계산하는데, 이 계산한 값을 버리지 않고 간선에 저장한다.  

다음 정점 v와의 거리가 v와 연결된 간선의 최소값보다 작다면 현재 정점 u를 v의 부모로 설정하고 minDist도 변경한다.  
그런데 이 문제에서는 선택된 간선의 목록이 필요하지 않으니 parent를 사용하지 않아도 된다.  

이 과정을 V번 반복하면 최소 스패닝 트리의 간선의 값의 합을 구할 수 있다.  
```c++
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

const int INF=987654321;
const int MAX_V=501;

int V;
int adj[MAX_V][MAX_V];
int X[MAX_V];
int Y[MAX_V];

int calcDistSqr(const int u, const int v)
{
    return adj[u][v]=adj[v][u]=(pow(X[u]-X[v],2)+pow(Y[u]-Y[v],2));
}

double prim()
{
  	vector<bool> added(V,false);
  	vector<int> minDistSqr(V,INF), parent(V,-1);
  	double ret=0;
  	minDistSqr[0]=parent[0]=0;
  	for(int it=0;it<V;++it)
  	{
        int u=-1;
        for(int v=0;v<V;++v)
            if(!added[v] && (u==-1 || minDistSqr[u]>minDistSqr[v]))
            {       
                u=v;
                // 0보다 작은 값은 없다.  
                if(minDistSqr[u]==0) 
                    break;
            }
        
        ret+=sqrt(minDistSqr[u]);
        added[u]=true;
        
        for(int v=0;v<V;++v)
        {
            if(added[v])
                continue;
            
            int distSqr=adj[u][v]==INF ? calcDistSqr(u,v) : adj[u][v];
            minDistSqr[v]=min(minDistSqr[v],distSqr);
        }
  	}
  	return ret;
}

int main()
{
    int testCase;
    cin>>testCase;
    
    cout<<fixed;
    cout.precision(10);
    
    while(testCase--)
    {
        int m;
        cin>>V>>m;
        
        for(int i=0;i<V;++i)
            for(int j=0;j<V;++j)
                adj[i][j]=INF;
        
        for(int i=0;i<V;++i)
            cin>>X[i];
        for(int i=0;i<V;++i)
            cin>>Y[i];
        
        for(int i=0;i<m;++i)
        {
            int u,v;
            cin>>u>>v;
            adj[u][v]=adj[v][u]=0;
        }
        
        cout<<prim()<<endl;
    }

    return 0;
}

```
