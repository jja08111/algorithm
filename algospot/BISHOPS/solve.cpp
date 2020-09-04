#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

// 대각선 방향: 왼쪽 아래로 내겨가는 대각선, 오른쪽 아래로 내려가는 대각선
const int dx[2]={-1,1};
const int dy[2]={ 1,1};

vector<string> board;
// id[dir][y][x]=dir방향 대각선을 따라 인접한 빈 칸 묶음들 중 (y,x)가 속한 묶음의 번호 
int id[2][8][8];
// 이분 그래프의 정보
int n,m;
int adj[64][64];
vector<int> bMatch;
vector<bool> visited;

bool dfs(int a)
{
    if(visited[a]) return false;
    visited[a]=true;
    for(int b=0;b<m;++b)
        if(adj[a][b])
            if(bMatch[b]==-1 || dfs(bMatch[b]))
            {
                bMatch[b]=a;
                return true;
            }
    return false;
}

// 최대 매칭 크기를 반환한다.  
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

int placeBishops()
{
    // 각 묶음에 번호를 붙인다.
    memset(id,-1,sizeof(id));
    // 각 대각선의 묶음 개수
    int count[2]={0,0};
    for(int dir=0;dir<2;++dir)
        for(int y=0;y<board.size();++y)
            for(int x=0;x<board.size();++x)
                if(board[y][x]=='.' && id[dir][y][x]==-1)
                {
                    int cy=y, cx=x;
                    // dir 대각선 방향에 있는 빈칸은 같은 id로 묶는다.
                    while(0<=cy && cy<board.size() &&
                          0<=cx && cx<board.size() && 
                          board[cy][cx]=='.')
                    {
                        id[dir][cy][cx]=count[dir];
                        cy+=dy[dir];
                        cx+=dx[dir];
                    }
                    count[dir]++;
                }
    // 이분 그래프를 만든다.
    n=count[0];
    m=count[1];
    memset(adj,0,sizeof(adj));
    for(int y=0;y<board.size();++y)
        for(int x=0;x<board.size();++x)
            if(board[y][x]=='.')
                adj[id[0][y][x]][id[1][y][x]]=1;
    
    return bipartiteMatch();
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int size;
        cin>>size;
        board.clear();
        for(int i=0;i<size;++i)
        {
            string line;
            cin>>line;
            board.push_back(line);
        }
        
        cout<<placeBishops()<<endl;
    }
    
    return 0;
}
