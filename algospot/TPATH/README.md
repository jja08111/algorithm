# 해결 

이 문제는 먼저 용어를 정의하고 해결하겠다.  
- 상한 : 모든 간선의 가중치가 이 값보다 작거나 같다.
- 하한 : 모든 간선의 가중치가 이 값보다 크거나 같다. 
- 경로의 너비 : 경로의 최소 상한과 최대 하한의 차이
---
문제를 해결하기 위해 경로의 상한과 하한을 동시에 찾기 보다는  
다음과 같이 하한은 고정하고 상한을 찾아가는 방식으로 해결해 나가면 쉽다.  

- minUpperBound(low) = 하한이 low이면서 시작점과 도착점을 연결하는 경로의 최소 상한은?  

모든 하한에 대해 위 함수를 수행하여 최소인 상한과 하한의 값을 찾으면 된다.  
이때 모든 간선의 가중치 목록을 정렬하여 저장해 두면 하한을 차례로 쉽게 접근할 수 있어 좋다.

```c++
const int MAX_V=2001;
const int INF=987654321;

int V,E;
vector<pair<int,int> > adj[MAX_V];
vector<int> weights;

int minWeightDifference()
{
    int ret=INF;
    for(int i=0;i<weights.size();++i)
        ret=min(ret,minUpperBound(i)-weights[i]);
    return ret;
}

```

위와 같은 설정이 되었으면 minUpperBound()를 구현해야 한다.

---
### 1. 크루스칼의 최소 스패닝 트리 이용

하나의 방법은 크루스칼의 최소 스패닝 트리를 구하는 알고리즘을 이용하는 것이다.  

미리 모든 간선에 대해 가중치 별로 정렬한 뒤, 하한보다는 작은 가중치를 제외한 가중치들을 탐색한다.  

탐색시 작은 가중치를 가진 간선부터 DisjointSet을 이용하여 최소 스패닝 트리 추가한다.  
간선을 추가했는데 목표하는 경로가 연결된 경우 마지막에 추가한 간선의 가중치를 반환하면 최소 상한을 얻을 수 있다.  
```c++
// 미리 계산해 둔다.
vector<pair<int,pair<int,int> > > edges;

int minUpperBound(int low)
{
    DisjointSet sets(V);
    for(int i=0;i<edges.size();++i)
    {
        if(edges[i].first<weights[low])
            continue;
        sets.merge(edges[i].second.first, edges[i].second.second);
        if(sets.find(0)==sets.find(V-1))
            return edges[i].first;
    }
    return INF;
}
```
