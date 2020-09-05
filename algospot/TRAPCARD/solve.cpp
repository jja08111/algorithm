#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
const int MAX=200;

int H,W;
vector<string> board;

int n,m;
bool adj[MAX][MAX];
// 각 칸을 표현하는 정점의 번호를 계산한다.
vector<vector<int> > id;
// 각 정점에 매칭된 상대 정점의 번호를 저장한다. 매칭되지 않은 경우 -1
vector<int> aMatch, bMatch;
// aChosen[i]=최대 독립 집합에 A_i가 포함되었는가?
// bChosen[i]=최대 독립 집합에 B-i가 포함되었는가?
vector<bool> aChosen, bChosen, visited;

inline bool inRange(const int y, const int x)
{
    return 0<=y && y<H  && 0<=x && x<W;
}

void makeGraph()
{
    id=vector<vector<int> >(H,vector<int>(W,-1));
    // 각 칸을 순회하며 번호를 매긴다.
    n=m=0;
    for(int y=0;y<H;++y)
        for(int x=0;x<W;++x)
            if(board[y][x]!='#')
            {
                if((y+x)%2==0)
                    id[y][x]=n++;
                else
                    id[y][x]=m++;
            }
    memset(adj,false,sizeof(adj));
    // 격자로 칠해진 칸(A)에 대해 인접한 칸을 검사한다.
    for(int y1=0;y1<H;++y1)
        for(int x1=0;x1<W;++x1)
            if((y1+x1)%2==0 && board[y1][x1]!='#')
            {
                // (y1,x1)의 모든 인접한 칸을 검사한다.
                for(int k=0;k<4;++k)
                {
                    int y2=y1+dy[k], x2=x1+dx[k];
                    if(inRange(y2,x2) && board[y2][x2]!='#')
                        adj[id[y1][x1]][id[y2][x2]]=true;
                }
            }
}

bool dfs(int a)
{
    if(visited[a]) return false;
    visited[a]=true;
    for(int b=0;b<m;++b)
        if(adj[a][b])
            if(bMatch[b]==-1 || dfs(bMatch[b]))
            {
                aMatch[a]=b;
                bMatch[b]=a;
                return true;
            }
    return false;
}

int bipartiteMatch()
{
    int ret=0;
    aMatch=vector<int>(n,-1);
    bMatch=vector<int>(m,-1);
    for(int start=0;start<n;++start)
    {
        visited=vector<bool>(n,false);
        if(dfs(start))
            ++ret;
    }
    return ret;
}

// 이분 그래프의 정보가 주어질 때 실제 최대 독립 집합을 계산한다.
int calcMaxIndependentSet()
{
    // aMatch[]와 bMatch[]를 계산한다.
    int C=bipartiteMatch();
    // 1. A의 모든 정점들을 선택하고, B에서 대응되지 않은 정점들을 선택한다.
    aChosen=vector<bool>(n,true);
    bChosen=vector<bool>(m,false);
    for(int i=0;i<m;++i)
        if(bMatch[i]==-1)
            bChosen[i]=true;
    // 2. 두 정점이 연결되어 있을 경우, 그중 A의 정점을 지우고 B의 대응된 정점을 대신 선택한다. 
    // 더 이상 변화가 일어나지 않을 때까지 반복한다.
    while(true)
    {
        bool changed=false;
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
                if(aChosen[i] && bChosen[j] && adj[i][j])
                {
                    // A는 항상 매칭에 포함된 정점임을 증명할 수 있다.
                    //assert(aMatch[i]!=-1);
                    aChosen[i]=false;
                    bChosen[aMatch[i]]=true;
                    changed=true;
                }
        if(!changed) break;
    }
    return C;
}

void printUpdatedBoard()
{
    for(int y=0;y<H;++y)
    {
        for(int x=0;x<W;++x)
        {
            if(board[y][x]=='#')
                cout<<'#';
            else if(((y+x)%2==0 && aChosen[id[y][x]]) ||
                    ((y+x)%2==1 && bChosen[id[y][x]]))
                cout<<'^';
            else 
                cout<<'.';
        }
        cout<<endl;
    }
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>H>>W;
        board.clear();
        for(int i=0;i<H;++i)
        {
            string s;
            cin>>s;
            board.push_back(s);
        }
        
        makeGraph();
        int maxSet=calcMaxIndependentSet();
        
        cout<<n+m-maxSet<<endl;
        printUpdatedBoard();
    }
    return 0;
}
