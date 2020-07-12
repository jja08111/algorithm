 # 해결 
처음에 보자마자 떠오른 생각은 "두 노드의 공통 조상 중 최소값을 찾으면 되는데 어떻게 [RMQ](https://github.com/jja08111/algorithm/tree/master/algospot/MORDOR) 클래스를 이용하지?" 이었다.  
이 문제는 트리에서 두 노드의 최소 공통 조상(least/lowest common ancestor, LCA)를 찾는 문제와 밀접하게 연관되어 있다.  
그렇다면 어떻게 LCA를 찾는다는 말인가?  

### 트리를 일렬로 펴보자 
![tree](https://algospot.com/media/judge-attachments/52a11e471716e8816ece02feb792f583/a.png)

위 트리는 전위순회 순서로 각 노드가 시리얼 넘버링 되어있다. 이렇게 하면 부모 노드는 자식 노드보다 번호가 앞에 있게 된다.  
이 트리를 재귀호출하여 순회하는데 이때 재귀호출후 다시 돌아오는 부분도 기록하면 다음과 같다.  
- 0 1 2 1 3 4 3 5 3 1 0 6 7 6 0 8 9 10 9 11 9 8 12 8 0

이 경로의 길이는 전체 간선이 n-1개 이니 내려갔다 올라오는 2번을 반복하기 때문에 2n-2인데, 여기서 루트에서 시작하니 길이는 2n-1이다.  
손으로 전위 순회과정을 따라가 보면 아래와 같은 점을 깨달을 수 있다.  
- u를 포함하는 서브트리에서 v를 포함하는 서브트리로 넘어가려면 LCA(u,v)를 항상 거쳐야한다.  
- LCA(u,v)의 부모 노드를 방문하려면 LCA(u,v)를 루트로 하는 서브트리는 이미 방문한 후여야 한다.  
 
이와 같은 특성을 이용하여 트리의 순회 결과를 저장한다.  
```c++
const int MAX_N=100000;
int n;
vector<int> child[MAX_N];
int no2serial[MAX_N], serial2no[MAX_N];
// trip에서 노드가 처음으로 등장하는 위치 저장, 노드의 깊이 저장(index는 node이다!!)
int locInTrip[MAX_N], depth[MAX_N];
int nextSerial;

void traverse(int here, int d, vector<int>& trip)
{
    // 첫 방문시 바로 일련 번호 부여
    no2serial[here]=nextSerial;
    serial2no[nextSerial]=here;
    ++nextSerial;
    // 현재 노드의 깊이 저장
    depth[here]=d;
    // trip에서 here노드가 처음 등장하는 위치를 저장
    locInTrip[here]=trip.size();
    trip.push_back(no2serial[here]);
    // 모든 자식 노드를 방문
    for(int i=0;i<child[here].size();++i)
    {
        traverse(child[here][i],d+1,trip);
        // 자식 노드를 방문하고 현재 노드로 돌아올 때마다 다시 추가하기
        trip.push_back(no2serial[here]);
    }
}

RMQ* prepareRMQ()
{
    nextSerial=0;
    // 순회 과정에서 만나는 노드들의 일련번호를 담는다.
    vector<int> trip;
    traverse(0,0,trip);
    return new RMQ(trip);
}
```
### 실제 거리 구하기 
10과 12의 LCA는 손으로 따라가 보면 알 수 있듯이 각 노드가 처음 방문하는 위치를 알면 부분 수열 {10,9,11,9,8,12}의 LCA가 8이라는 것을 알 수 있다.  
LCA를 알아내었으면 두 노드와 LCA의 거리를 depth를 이용하여 계산하면 경로의 길이를 구할 수 있다.  
```c++
int distance(RMQ* rmq, int u, int v)
{
    // trip 배열에서 u와 v의 첫 출현 위치를 찾는다.  
    int lu=locInTrip[u], lv=locInTrip[v];
    if(lu>lv)
        swap(lu,lv);
    int lca=serial2no[rmq->query(lu,lv)];
    return depth[u]+depth[v]-2*depth[lca];
}
```
