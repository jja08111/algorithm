# 해결 
'절들을 이루는 식이 참이 되는가?'를 구하는 문제이다. 

하나의 절을 이루는 두 불리언 변수가 A, B 라고 하면 !A 이면 B가 참이어야 한다. 반대로 !B 이면 A가 참이어야 한다.  
이런 식으로 그래프를 형성하고 그래프를 SCC별로 묶는다.  

SCC로 묶는 이유는 한 사이클 내에 !A 와 A가 같이 존재하는 경우 식을 참으로 만들 수 없는 것을 찾기 위해서이다.  
!A 와 A가 한 사이클 내에 같이 존재하면 답이 안되는 이유는 **두 정점 중 하나는 참, 하나는 거짓인데 이는 절 (A||A)가 거짓인 경우 생성되는 간선 !A->A를 포함하기 때문이다.**

눈여겨 볼 부분은 각 정점을 형성할때 함수를 구현한 것이고, not a를 비트 연산자 ^ 를 이용하여 쉽게 구한 것이다.
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

// convert : i = 2t, not i = 2t+1
inline int convertNumToVertex(int n)
{
    if(n>0)
        return (n-1)*2;
    return (-1*n)*2-1;
}

int scc(int here)
{
    int ret=discovered[here]=vertexCounter++;
    st.push(here);
    for(int i=0;i<adj[here].size();++i)
    {
        int there=adj[here][i];
        if(discovered[there]==-1)
            ret=min(ret,scc(there));
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

void makeSCC()
{
    discovered=sccId=vector<int>(adj.size(),-1);
    sccCounter=vertexCounter=0;
    for(int i=0;i<adj.size();++i)
        if(discovered[i]==-1)
            scc(i);
}

int canMakeFuncTrue()
{
    for(int i=0;i<adj.size();i+=2)
        if(sccId[i]==sccId[i+1])
            return 0;
    return 1;
}

int main(void)
{
    int n,m;
    cin>>n>>m;
    
    adj.clear(); adj.resize(n<<1);
    
    for(int i=0;i<m;++i)
    {
        int a,b;
        cin>>a>>b;
        a=convertNumToVertex(a);
        b=convertNumToVertex(b);
        
        adj[a^1].push_back(b); // ~a -> b
        adj[b^1].push_back(a); // ~b -> a
    }
    makeSCC();
    cout<<canMakeFuncTrue()<<endl;
    return 0;
}
```
# 참조 
https://devbelly.tistory.com/54
