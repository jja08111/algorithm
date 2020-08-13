# 해결 
이 문제는 조작을 통해 어느 한 심사위원의 선택이 둘 다 거짓이 되면 안되는 문제이다.  
즉 [2-SAT문제](https://github.com/jja08111/algorithm/tree/master/backjoon/%5B11281%5D2-SAT%20-%204)라고 볼 수 있다.  

이때 원근(0번 참가자)이가 조작을 통해 올라갈 수 있는지 확인해야 하는데 이는 SCC들이 위상정렬의 역순으로 된 부분을 이용하여 해결 할 수 있다.  
바로 0번 변수가 나타났을 때 거짓인 변수가 먼저 나와야 조작이 가능하고 참인 변수가 먼저 나오면 조작이 불가하다.  

왜 위상정렬 순으로 정점들을 거짓으로 처리하냐면 참으로 처리하면 참에서 거짓으로 가는 정점이 나올 수 있다.  
참에서 거짓으로 가는 정점은 어느 절 (A||B)가 거짓이라고 가정했을 때 !A->B의 두 변수 A,B가 둘 다 거짓이니 참에서 거짓으로 가는 정점이기 때문에 참에서 거짓으로 가는 정점은 나오면 안되게 해야한다.  
```c++
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

vector<vector<int> > adj;
vector<int> discovered, sccId;
stack<int> st;
int sccCounter, vertexCounter;

inline int convert(int n)
{
    if(n>0)
        return 2*(n-1);
    return -2*(n+1)+1;
}

int dfs(int here)
{
    int ret=discovered[here]=vertexCounter++;
    st.push(here);
    for(int i=0;i<adj[here].size();++i)
    {
        int there=adj[here][i];
        if(discovered[there]==-1)
            ret=min(ret,dfs(there));
        else if(sccId[there]==-1)
            ret=min(ret,discovered[there]);
    }
    if(ret==discovered[here])
    {
        while(true)
        {
            int t=st.top();
            st.pop();
            sccId[t]=sccCounter;
            if(t==here) break;
        }
        sccCounter++;
    }
    return ret;
}

void makeSCCs()
{
    discovered=sccId=vector<int>(adj.size(),-1);
    sccCounter=vertexCounter=0;
    for(int i=0;i<adj.size();++i)
        if(discovered[i]==-1)
            dfs(i);
}

bool canMakeList()
{
    int n=adj.size();
    
    makeSCCs();
    
    for(int i=0;i<n;i+=2)
        if(sccId[i]==sccId[i+1])
            return false;
    
    vector<pair<int,int> > order;
    for(int i=0;i<n;++i)
        order.push_back(make_pair(-sccId[i],i));
    sort(order.begin(),order.end());
    
    for(int i=0;i<n;++i)
    {
        int vertex=order[i].second;
        int variable=vertex/2;
        bool isTrue=(vertex%2==0);
        if(variable==0)
            return !isTrue;
    }
}

int main()
{
    int n,m;
    while(scanf("%d %d",&n,&m)!=-1)
    {
        adj.clear(); adj.resize(n*2);
        
        for(int i=0;i<m;++i)
        {
            int a,b;
            cin>>a>>b;
            a=convert(a);
            b=convert(b);
            adj[a^1].push_back(b); // !a -> b
            adj[b^1].push_back(a); // !b -> a
        }
        
        if(canMakeList())
            cout<<"yes"<<endl;
        else
            cout<<"no"<<endl;
    }

    return 0;
}

```

# 회고 
상근이가 올라가는 경우가 있어야 한다는 조건을 읽지 않아 틀렸었다.  
문제를 제대로 읽자  
