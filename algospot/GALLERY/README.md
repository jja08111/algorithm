# 해결 
카메라 설치를 최소화 하기 위해서는 맨 끝에 있는 방에는 설치하지 않아야 한다.  
이때 한번 방문한 방을 다시 가기 위해서는 지났던 복도를 다시 지나야 한다는 말이 있는데 이것은 그래프에 사이클이 없다는 말이다.  
이는 그래프의 상하관계가 없는 루트없는 트리라고 할 수 있다.  

트리에서 한 노드부터 DFS를 실시하며 현재 노드를 unwatched, watched, installed 형태로 표현하여 해결할 수 있다.  
잎노드는 설치하지 않고 올라오며 자손노드중 하나라도 unwatched인 노드가 있다면 install한다.  
이런식으로 상태를 반환하며 현재 노드에 자식 노드들의 정보를 저장하면 해결할 수 있다.  

여기서 주의할 점은 트리가 여러개 있을 수 있다는 점과 탐색을 시작한 노드가 unwatched인 경우를 고려하여 구현해야 한다는 것이다.  
```c++
#include <iostream>
#include <vector>
using namespace std;

const int MAX_N=1001;

enum
{
    UNWATCHED,WATCHED,INSTALLED
}; 

vector<int> adj[MAX_N];
vector<bool> visited;
int install;

int dfs(int here)
{
    visited[here]=true;
    int children[3]={0,0,0};
    for(int i=0;i<adj[here].size();++i)
    {
        int there=adj[here][i];
        if(!visited[there])
            children[dfs(there)]++;
    }
    
    if(children[UNWATCHED])
    {
        ++install;
        return INSTALLED;
    }
    if(children[INSTALLED])
        return WATCHED;
    return UNWATCHED;
}


int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int g,h;
        cin>>g>>h;
        
        visited=vector<bool>(g,false);
        install=0;
        
        for(int i=0;i<h;++i)
        {
            int a,b;
            cin>>a>>b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        
        for(int i=0;i<g;++i)
            if(!visited[i] && dfs(i)==UNWATCHED)
                install++;
        
        cout<<install<<endl;
        
        for(int i=0;i<g;++i)
            adj[i].clear();
    }

    return 0;
}
```
