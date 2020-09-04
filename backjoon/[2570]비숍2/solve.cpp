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
// true: 빈 칸, fals: 장애물
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
