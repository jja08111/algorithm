# 해결 
플로이드 알고리즘을 이용하여 해결했다.  
도달하지 못하는 정점은 INF로 초기화 하였다.  

여기서 주의할 점은 i번 정점에서 i번 정점으로 무조건 갈 수 있는 것이 아닌 부분이다.  
그렇기 때문에 i번 정점에서 i번 정점으로 가는 간선은 INF로 초기화 되어있어야 한다.  
```c++
#include <iostream>
#include <vector>
using namespace std;

const int MAX_V=101;
const int INF=987654321;

int V;
int adj[MAX_V][MAX_V];

void floyd()
{
    for(int k=0;k<V;++k)
        for(int i=0;i<V;++i)
            for(int j=0;j<V;++j)
                adj[i][j]=min(adj[i][j],adj[i][k]+adj[k][j]);
}

void printResult()
{
    for(int i=0;i<V;++i)
    {
        for(int j=0;j<V;++j)
            cout<<(adj[i][j]==INF ? 0:1)<<' ';
        cout<<endl;
    }
}

int main()
{
    cin>>V;
    for(int i=0;i<V;++i)
        for(int j=0;j<V;++j)
        {
            cin>>adj[i][j];
            if(adj[i][j]==0)
                adj[i][j]=INF;
        }
    
    floyd();
    printResult();
    return 0;
}
```
