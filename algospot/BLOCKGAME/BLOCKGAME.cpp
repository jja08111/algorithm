#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

vector<int> moves;
int n;
char cache[1<<25];

// 셀의 위치(y,x)를 비트로 변환(y*5+x) 해준다.
inline int cell(int y,int x)
{
    return 1<<(y*5+x);
}

// 블록이 있으면 비트가 켜진다.
void init(int& board)
{
    for(int y=0;y<5;++y)
        for(int x=0;x<5;++x)
        {
            char tmp; cin>>tmp;
            if(tmp=='#')
                board|=cell(y,x);
        }
    memset(cache,-1,sizeof(cache));
}

void preCalc(void)
{
    //4칸 블록 계산
    for(int y=0;y<4;++y)
        for(int x=0;x<4;++x)
        {
            vector<int> cells;
            for(int dy=0;dy<2;++dy)
                for(int dx=0;dx<2;++dx)
                    cells.push_back(cell(y+dy,x+dx));
            //2X2 꽉차있는 셀에서 하나씩 빼며 만든다.
            int square=cells[0]+cells[1]+cells[2]+cells[3];
            for(int i=0;i<4;++i)
                moves.push_back(square-cells[i]);
        }
    //2칸 블록 계산
    for(int i=0;i<5;++i)
        for(int j=0;j<4;++j)
        {
            moves.push_back(cell(i,j)+cell(i,j+1));
            moves.push_back(cell(j,i)+cell(j+1,i));
        }
}

char play(int board)
{
    char& ret=cache[board];
    if(ret!=-1)
        return ret;
    
    ret=0;
    for(int i=0;i<moves.size();++i)
        // 배치가능할때
        if((board & moves[i]) == 0)
            // 상대가 이길 수 없으면 이긴 것이다.
            if(!play(board | moves[i]))
            {
                ret=1;
                break;
            }
    
    return ret;
}

int main(void)
{
    int testCase; cin>>testCase;
    
    while(testCase--)
    {
        int board=0;
        
        init(board);
        preCalc();
        
        if(play(board))
            cout<<"WINNING"<<endl;
        else
            cout<<"LOSING"<<endl;
    }
    
    return 0;
}
