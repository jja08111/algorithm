#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int boardHeight,boardWidth;
vector<string> board;
int isCovered[10][10];
int best;

int blockSize;
vector<vector<pair<int,int> > > rotations;

vector<string> rotate(const vector<string>& arr)
{
    //90도 회전해야 하니 arr[0].size()와 arr.size()의 위치가 바뀐것을 눈여겨 보자
    vector<string> ret(arr[0].size(),string(arr.size(),' '));
    for(int i=0;i<arr.size();++i)
        for(int j=0;j<arr[0].size();++j)
            ret[j][arr.size()-1-i]=arr[i][j];
    return ret;
}

void generateRotations(vector<string> block)
{
    rotations.clear();
    rotations.resize(4);
    for(int rot=0;rot<4;++rot)
    {
        int originY=-1, originX=-1;
        for(int i=0;i<block.size();++i)
            for(int j=0;j<block[i].size();++j)
                if(block[i][j]=='#')
                {
                    //가장 윗줄 맨 왼쪽에 있는 칸이 원점이 된다.
                    if(originY==-1)
                    {
                        originY=i;
                        originX=j;
                    }
                    //각 칸의 위치를 원점으로부터의 상대좌표로 표현한다.
                    rotations[rot].push_back(make_pair(i-originY,j-originX));
                }
        //블록을 시계방향으로 90도 회전한다.
        block=rotate(block);
    }
    sort(rotations.begin(),rotations.end());
    //중복되는 블럭을 제거한다.
    rotations.erase(unique(rotations.begin(),rotations.end()), rotations.end());
    blockSize=rotations[0].size();
}

bool inRange(const int y, const int x)
{
    return 0<=y && y<boardHeight && 0<=x && x<boardWidth;
}

bool set(int y, int x, const vector<pair<int,int> >& blocksPosition, int delta)
{
    bool canSet=true;
    for(int i=0;i<blockSize;++i)
    {
        int ny=y+blocksPosition[i].first;
        int nx=x+blocksPosition[i].second;
        
        if(!inRange(ny,nx))
            canSet=false;
        else if((isCovered[ny][nx]+=delta)>1)
            canSet=false;
    }
    return canSet;
}

bool canPruneBlock(int placedBlockNum)
{
    int emptyCell=0;
    for(int i=0;i<boardHeight;++i)
        for(int j=0;j<boardWidth;++j)
            emptyCell+=(isCovered[i][j]==0 ? 1 : 0);
    //남은 칸 개수가 블록을 놓아도 현재의 최적해보다 작거나 같을때
    return (emptyCell/blockSize)+placedBlockNum<=best;
}

void search(int placedBlockNum)
{
    if(canPruneBlock(placedBlockNum))
        return;
    
    //아직 채우지 못한 맨 윗줄의 왼쪽 칸을 찾는다.
    int y=-1,x=-1;
    for(int i=0;i<boardHeight;++i)
    {
        for(int j=0;j<boardWidth;++j)
            if(isCovered[i][j]==0)
            {
                y=i;
                x=j;
                break;
            }
        if(y!=-1)
            break;
    }
    //기저사례: 모든 칸을 처리한 경우
    if(y==-1)
    {
        best=max(best,placedBlockNum);
        return;
    }
    //현재 칸에 블록을 배치한다.
    for(int i=0;i<rotations.size();++i)
    {
        if(set(y,x,rotations[i],1))
            search(placedBlockNum+1);
        set(y,x,rotations[i],-1);
    }
    //이 칸을 덮지 않고 '막아'둔다.
    isCovered[y][x]=1;
    search(placedBlockNum);
    isCovered[y][x]=0;
}

int solve()
{
    best=0;
    for(int i=0;i<boardHeight;++i)
        for(int j=0;j<boardWidth;++j)
            isCovered[i][j]=(board[i][j]=='#' ? 1 : 0);
    
    search(0);
    return best;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        board.clear();
        vector<string> block;
        int blockHeight, blockWidth;
        cin>>boardHeight>>boardWidth>>blockHeight>>blockWidth;
        
        for(int i=0;i<boardHeight;++i)
        {
            string tmp;
            cin>>tmp;
            board.push_back(tmp);
        }
        for(int i=0;i<blockHeight;++i)
        {
            string tmp;
            cin>>tmp;
            block.push_back(tmp);
        }
        
        generateRotations(block);
        
        cout<<solve()<<endl;
    }
    
    return 0;
}
