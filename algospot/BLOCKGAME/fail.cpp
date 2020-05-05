/*
무작정 만들었던 코드이지만 능력이 부족하다.

#include <iostream>
using namespace std;

const int dx3[4][3]={{0,0,-1},{0,0,1},{0,1,1},{0,1,0}};
const int dy3[4][3]={{0,1,1}, {0,1,1},{0,0,1},{0,0,1}};

const int dx2[2][2]={{0,1},{0,0}};
const int dy2[2][2]={{0,0},{0,1}};

const char INSERT_BLOCK='#'-'.';

int n;
int cache[5][5];

void init(char& map[5][5])
{
    for(int y=0;y<5;++y)
        for(int x=0;x<5;++x)
            cin>>map[y][x];
}

bool inRange(const int y, const int x)
{
    return 0<=y && y<5 && 0<=x && x<5;
}

bool canPlace(char& map[5][5], int setting, int y, int x, int delta)
{
    bool isPossible=true;
    //L자 모양일때
    if(setting<4)
        for(int i=0;i<3;++i)
        {
            int ny=dy3[setting][i]+y;
            int nx=dx3[setting][i]+x;
            
            if(inRange(ny,nx))
            {
                map[ny][nx]+=INSERT_BLOCK*delta;
                if(map[ny][nx]>'#')
                    isPossible=false;
            }
        }
    else
        for(int i=0;i<2;++i)
        {
            int ny=dy2[setting][i]+y;
            int nx=dx2[setting][i]+x;
            
            map[ny][nx]+=INSERT_BLOCK*delta;
            if(map[ny][nx]>'#')
                isPossible=false;
        }
    
    return isPossible;
}

int canWin(char map[5][5])
{
    int& ret=cache
    if(ret!=-2)
        return ret;
    
    ret=-1;
    for(int y=0;y<5;++y)
        for(int x=0;x<5;++x)
            //블럭이 비워져 있는 곳을 찾는다.
            if(map[y][x]=='.')
            {
                //비워진 곳에 놓을 수 있는지 확인한다.
                for(int setting=0;setting<6;++setting)
                {
                    if(canPlace(map,setting,y,x,1))
                        ret= -canWin(map);
                    canPlace(map,setting,y,x,-1);
                }
            }
    //놓을 수 없게 되면 -1일테고 위치시켰다면 1일 것이다.?
    return ret;
}

int main(void)
{
    int testCase; cin>>testCase;
    
    while(testCase--)
    {
        char map[5][5];
        init(map);
        
        if(canWin(map)==1)
            cout<<"WINNING"<<endl;
    }
    
    return 0;
}

*/
