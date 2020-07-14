# 해결 
두 개의 에디터를 가지고 각각의 지지자들의 집합을 구하는 문제이다.  
당연히 상호 베타적 집합(Union-find)을 떠올릴 수 있다.  
상호 베타적 집합에 대해 간단히 설명하자면 1차원 배열을 통해 공통 원소가 없는 상호 배타적인 부분 집합들로 나눠진 원소들을 저장하고 조작하는 자료구조이다.  
집합은 루트를 기준으로 표현한다.  
이 자료구조는 기본적인 구현에서 약간의 최적화를 거치면 속도가 꽤 향상된다.  

이 문제에서는 2가지의 집합으로만 나눠진다.  
댓글의 정보를 가지고 분류를 해야하는데 적의 적은 아군, 아군의 적과 아군의 적은 서로 아군이라는 점을 유념해야한다.  

서로 아군이라는 것을 알게 되었으면 두 집합을 합쳐야 하는데 이때 적군이 없는 경우를 -1로 표현하여 예외 처리해야 한다.  
```c++
struct BipartiteUnionFind {
    vector<int> parent, rank, enemy, size;
    BipartiteUnionFind(int n) : parent(n), rank(n,1), enemy(n,-1), size(n,1) {
        for(int i=0;i<n;++i)
            parent[i]=i;
    }
    int find(int u) {
        if(u==parent[u])
            return u;
        return parent[u]=find(parent[u]);
    }
    // 두 개의 집합을 묶고 루트를 반환한다.  
    int merge(int u, int v) {
        // 예외 처리
        if(u==-1 || v==-1)
            return max(u,v);
        
        u=find(u), v=find(v);
        if(u==v)
            return u;
        
        if(rank[u]>rank[v])
            swap(u,v);
        if(rank[u]==rank[v])
            ++rank[v];
        
        parent[u]=v;
        size[v]+=size[u];
        
        return v;
    }
    bool dis(int u, int v) {
        u=find(u), v=find(v);
        if(u==v)
            return false;
        // 적의 적은 아군이니 같은 집합에 묶는다.
        int a=merge(u,enemy[v]), b=merge(enemy[u],v);
        enemy[a]=b, enemy[b]=a;
        return true;
    }
    bool ack(int u, int v) {
        u=find(u), v=find(v);
        if(enemy[u]==v)
            return false;
        int a=merge(u,v), b=merge(enemy[u],enemy[v]);
        enemy[a]=b;
        if(b!=-1)
            enemy[b]=a;
        return true;
    }
};
```

댓글을 모두 읽은 후에는 최대 개체수를 구해야 한다.  
이때 적군을 표현하는 쌍을 두번 중복하여 세지 않도록 주의해야 하며, 적이 아예 없는 경우는 자동으로 한번씩만 셀 수밖에 없다.  
```c++
int maxParty(const BipartiteUnionFind& buf)
{
    int ret=0;
    for(int node=0;node<n;++node)
        if(buf.parent[node]==node)
        {
            int enemy=buf.enemy[node];
            // 같은 모임 쌍을 두번 세지 않는 방법
            if(enemy>node)
                continue;
            int mySize=buf.size[node];
            int enemySize=(enemy==-1 ? 0 : buf.size[enemy]);
            ret+=max(mySize,enemySize);
        }
    return ret;
}
```
# 회고 
```c++
if(ok && (prefer[0]=='D' && !buf.dis(u,v)) || (prefer[0]=='A' && !buf.ack(u,v)))
```
위와 같은 연산자는 ok가 false 여도 맨 오른쪽이 true면 true가 되기 때문에 문제있는 코드이다.  
저런식으로 구현했다가 틀렸었다. 헷갈릴 우려가 있어서 구현시 ok를 아예 위쪽으로 빼버렸다.
