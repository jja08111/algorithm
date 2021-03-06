# 해결  
종만북의 [BISHOP](https://algospot.com/judge/problem/read/BISHOPS)문제와 거의 동일하며 [풀이](https://github.com/jja08111/algorithm/tree/master/algospot/BISHOPS) 또한 비슷하다.  

비숍이 대각선으로만 이동할 수 있는데 이는 문제에서 주어진 맵에서 특정한 비숍이 있으면 그 비숍을 기준으로 오른쪽 아래 대각선(rd), 왼쪽 아래 대각선(ld) 방향으로는 비숍을 둘 수 없다는 것을 알 수 있다.  

대각선 방향으로 연속한 빈 칸들을 묶어버리면 ld 기준으로 rd를 선택하는 이분매칭 문제가 된다.  
즉, rd 그룹과 ld 그룹으로 나누어 같은 빈 칸을 공유하면 간선으로 이어 최대 유량을 찾으면 된다.  

그룹을 나누는 것은 같은 반복적으로 그룹내에 속한 빈 칸들에 같은 번호를 부여하는 식으로 구현하였다.  
이후 모든 정점을 돌아보며 빈 칸인 경우 해당 정점의 ld에서 rd로 가는 간선을 연결하였다.  
이 다음에는 이분 매칭에서 최대유량을 구하는 방법으로 답을 얻었다.  
```c++
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAX=101;
// 왼쪽 아래, 오른쪽 아래 대각선
const int dx[2]={-1,1};
const int dy[2]={ 1,1};

// A그룹과 B그룹 각각의 크기
int n,m;
// true: 빈 칸, fales: 장애물
vector<vector<bool> > canPlace;
vector<vector<int> > adj;
vector<bool> visited;
vector<int> bMatch;
int id[2][MAX][MAX];

bool dfs(int a)
{
    if(visited[a]) return false;
    visited[a]=true;
    for(int i=0;i<adj[a].size();++i)
    {
        int b=adj[a][i];
        if(bMatch[b]==-1 || dfs(bMatch[b]))
        {
            bMatch[b]=a;
            return true;
        }
    }
    return false;
}

int bipartiteMatch()
{
    bMatch=vector<int>(m,-1);
    int ret=0;
    for(int start=0;start<n;++start)
    {
        visited=vector<bool>(n,false);
        if(dfs(start))
            ++ret;
    }
    return ret;
}

int placeBishop()
{
    int len=canPlace.size();
    int count[2]={0,0};
    memset(id,-1,sizeof(id));
    
    for(int dir=0;dir<2;++dir)
        for(int y=0;y<len;++y)
            for(int x=0;x<len;++x)
                if(canPlace[y][x] && id[dir][y][x]==-1)
                {
                    int cy=y, cx=x;
                    while(0<=cy && cy<len &&
                          0<=cx && cx<len && 
                          canPlace[cy][cx])
                    {
                        id[dir][cy][cx]=count[dir];
                        cy+=dy[dir];
                        cx+=dx[dir];
                    }
                    count[dir]++;
                }
    
    n=count[0];
    m=count[1];
    adj.resize(n+1);
    for(int y=0;y<len;++y)
        for(int x=0;x<len;++x)
            if(canPlace[y][x])
                adj[id[0][y][x]].push_back(id[1][y][x]);
    
    return bipartiteMatch();
}

int main()
{
    int size;
    cin>>size;
    canPlace=vector<vector<bool> >(size,vector<bool>(size,true));
    
    int blockNum;
    cin>>blockNum;
    for(int i=0;i<blockNum;++i)
    {
        int y,x;
        cin>>y>>x;
        --y; --x;
        canPlace[y][x]=false;
    }
    
    cout<<placeBishop()<<endl;
    return 0;
}
```
