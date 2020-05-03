#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX=19683;
int cache[MAX];

char getTurn(const vector<string>& board)
{
    int emptyCell=0;

    for(int y=0;y<3;++y)
        for(int x=0;x<3;++x)
            if(board[y][x]=='.')
                ++emptyCell;
    
    return emptyCell%2 ? 'x' : 'o';
}

void init(vector<string>& board, char& turn)
{
    for(int i=0;i<MAX;++i)
        cache[i]=-2;
    for(int i=0;i<3;++i)
        cin>>board[i];
    
    turn=getTurn(board);
}

bool isFinished(const vector<string>& board, char turn)
{
    bool ld=true, rd=true;
    
    for(int i=0;i<3;++i)
    {
        bool row=true, col=true;
        for(int j=0;j<3;++j)
        {
            //가로, 세로에서 일치 하지 않을 경우
            if(board[i][j]!=turn)
                row=false;
            if(board[j][i]!=turn)
                col=false;
            
            //대각선에서 일치하지 않을 경우
            if(board[i][i]!=turn)
                rd=false;
            if(board[i][2-i]!=turn)
                ld=false;
            
            //가로 혹은 세로에서 줄이 만들어진 경우
            if((row || col) && j==2)
                return true;
        }
        //대각선에서 줄이 만들어진 경우
        if((ld || rd) && i==2)
            return true;
    }
    return false;
}

//3진수로 게임판을 표현한다.
int bijection(const vector<string>& board)
{
    int ret=0;
    for(int y=0;y<3;++y)
        for(int x=0;x<3;++x)
        {
            ret*=3;
            if(board[y][x]=='o')
                ++ret;
            else if(board[y][x]=='x')
                ret+=2;
        }
    return ret;
}

//현재차례의 사람이 이기면 1, 비기면 0, 지면 -1을 반환한다.
int canWin(vector<string>& board, char turn)
{
    //마지막에 상대가 둬서 한 줄이 만들어진 경우
    if(isFinished(board, 'o'+'x'-turn))
        return -1;
    
    int& ret=cache[bijection(board)];
    if(ret!=-2)
        return ret;
    
    int minValue=2;
    for(int y=0;y<3;++y)
        for(int x=0;x<3;++x)
            if(board[y][x]=='.')
            {
                board[y][x]=turn;
                minValue=min(minValue,canWin(board,'o'+'x'-turn));
                board[y][x]='.';
            }
    
    //게임판이 꽉찼거나 어떻게 해도 비기는 경우
    if(minValue==2 || minValue==0)
        return ret=0;
    
    //상대가 지면 내가 이기고, 상대가 이기면 내가 진것이다.
    return ret = -minValue;
}

int main(void)
{
    int testCase; cin>>testCase;
    
    while(testCase--)
    {
        vector<string> board(3);
        char turn;
        
        init(board, turn);
        
        switch(canWin(board,turn))
        {
            case -1:
                cout<<(char)('x'+'o'-turn)<<endl; break;
            case 0:
                cout<<"TIE"<<endl; break;
            case 1:
                cout<<turn<<endl; break;
        }
    }

    return 0;
}
