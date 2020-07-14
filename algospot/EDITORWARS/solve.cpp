#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

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

int n,m;

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

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        scanf("%d %d",&n,&m);
        
        BipartiteUnionFind buf(n);
        bool ok=true;
        
        for(int i=0;i<m;++i)
        {
            char prefer[4];
            int u,v;
            scanf("%s %d %d",prefer,&u,&v);
            if(!ok)
                continue;
            
            if((prefer[0]=='D' && !buf.dis(u,v)) || (prefer[0]=='A' && !buf.ack(u,v)))
            {
                ok=false;
                printf("CONTRADICTION AT %d\n",i+1);
            }
        }
        if(ok)
            printf("MAX PARTY SIZE IS %d\n",maxParty(buf));
    }
    return 0;
}
