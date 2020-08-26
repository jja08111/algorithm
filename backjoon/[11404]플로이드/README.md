# 해결 
[플로이드 알고리즘](https://ko.wikipedia.org/wiki/%ED%94%8C%EB%A1%9C%EC%9D%B4%EB%93%9C-%EC%9B%8C%EC%85%9C_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98)을 이용하여 해결했다.  

주의할 점은 경로가 없는 경우 0을 출력해야 하는데 초기에 INF로 초기화 해주면 쉽게 경로가 없는지를 찾을 수 있다.  
그리고 시작 정점에서 도착 정점으로 가는 가중치가 여러개 있을 수 있어 더 작은 값을 저장해 주면 된다.  

```c++
#include <iostream>
#include <cstring>
using namespace std;

const int INF=987654321;
const int MAX_V=101;

int V;
int adj[MAX_V][MAX_V];

void floyd()
{
    for(int i=1;i<=V;++i)
        adj[i][i]=0;
    for(int k=1;k<=V;++k)
        for(int i=1;i<=V;++i)
            for(int j=1;j<=V;++j)
                adj[i][j]=min(adj[i][j],adj[i][k]+adj[k][j]);
}

int main()
{
    int E;
    cin>>V>>E;
    
    for(int i=1;i<=V;++i)
        for(int j=1;j<=V;++j)
            adj[i][j]=INF;
    
    for(int i=0;i<E;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        adj[a][b]=min(adj[a][b],c);
    }
    
    floyd();
    
    for(int i=1;i<=V;++i)
        for(int j=1;j<=V;++j)
        {
            if(adj[i][j]==INF)
                cout<<0<<' ';
            else
                cout<<adj[i][j]<<' ';
        }
        cout<<endl;
    
    return 0;
}

```
