# 해결 
처음에는 입력된 노드 a와 b가 있을 때 둘 중 부모가 이미 존재하는 노드가 부모가 되는 방식으로 구현했었다.  
트리는 부모가 하나인 구조를 이용한 것이다. 하지만 이 방식은 입력값이 정렬되어 순서대로 되어있지 않아 오류를 출력한다.  

위와 같은 오류를 해결하기 위해 트리를 양방향 간선으로 저장하고 DFS로 모든 값들을 순회하며 
자식 노드 인덱스에 부모 노드 값을 저장하는 방법을 사용할 수 있다.   
```c++
vector<int> tree[MAX];
int parent[MAX];
bool visited[MAX];

void getParent(int here)
{
    visited[here]=true;
    for(int there=0;there<tree[here].size();++there)
    {
        int cand=tree[here][there];
        if(!visited[cand])
        {
            parent[cand]=here;
            getParent(cand);
        }
    }
}
```
