# 해결 
BFS를 이용하여 최단거리로 목표하는 위치에 도달하는 경로를 찾는 문제이다.  

parent라는 배열을 이용하여 경로를 생성할 수 있으며 이미 발견한 정점을 표시하는 역할도 한다.  

만들어진 경로는 역순으로 되어있기 때문에 값을 거꾸로 출력해야 한다.  
```c++
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAX=100001;

int n,k;

inline bool inRange(int n)
{
    return 0<=n && n<MAX;
}

int nextVertex(const int here, const int select)
{
    int there;
    switch(select)
    {
    case 0: there=here*2; break;
    case 1: there=here-1; break;
    case 2: there=here+1; break;
    }
    
    if(inRange(there))
        return there;
    return -1;
}

vector<int> bfs()
{
    vector<int> parent(MAX,-1);
    queue<int> q;
    q.push(n);
    parent[n]=n;
    
    while(!q.empty())
    {
        int here=q.front();
        q.pop();
        
        if(here==k)
            return parent;
        
        for(int i=0;i<3;++i)
        {
            int there=nextVertex(here,i);
            if(there<0)
                continue;
            
            if(parent[there]==-1)
            {
                parent[there]=here;
                q.push(there);
            }
        }
    }
}

vector<int> getReverseRoute()
{
    vector<int> parent=bfs();
    vector<int> route;
    
    int here=k;
    while(parent[here]!=here)
    {
        route.push_back(here);
        here=parent[here];
    }
    route.push_back(n);
    
    return route;
}

int main()
{
    cin>>n>>k;
    
    vector<int> ret=getReverseRoute();
    
    cout<<ret.size()-1<<endl;
    for(int i=ret.size()-1;i>=0;--i)
        cout<<ret[i]<<' ';
    
    return 0;
}
```

### 주의사항 
- 다음 정점의 값을 찾을 때 범위에 주의해야 한다. nextVertex 함수의 조건문을 제대로 작성하지 않으면 잘못된 인덱스 참조로 런타임 에러가 발생하기 때문이다.   
- (목표하는 위치에 도달하면 종료하는 bfs함수 내의 조건문의 위치가 아래의 코드처럼 되어있으면 런타임 에러가 발생한다.(왜 그런지는 찾는 중이다...) -> 아마 n과 k가 같은 경우 문제가 발생하는 것 같다.) 
-> bfs함수가 while문을 탈출하는 경우 아무것도 반환하지 않아 잘못된 인덱스를 참조하기 때문이다.  
(차라리 parent를 전역으로 선언하는게 나을 듯 하다.)
```c++
vector<int> bfs()
{
    vector<int> parent(MAX,-1);
    queue<int> q;
    q.push(n);
    parent[n]=n;
    while(!q.empty())
    {
        int here=q.front();
        q.pop();
        
        // 목표하는 위치에 도달하면 종료 -> 올바른 위치
        if(here==k)
            return parent;
        ///////////////////////////
        for(int i=0;i<3;++i)
        {
            int there=nextVertex(here,i);
            if(there==-1)
                continue;
            
            if(parent[there]==-1)
            {
                parent[there]=here;
                // 잘못된 위치
                //if(there==k)
                //  return parent;
                //////////////////
                q.push(there);
            }
        }
    }
    //조건문 위치가 안에 위치하려면 아래의 반환값이 
    //return parent;
}
```
