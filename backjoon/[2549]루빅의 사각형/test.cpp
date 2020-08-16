#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <map>
using namespace std;

class State 
{
public:
    vector<int> tile[4];
public:
    State()
    {
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j)
                tile[i].push_back(4*i+j+1);
    }
    // 복사 생성자 
    State(const State& copy)
    {
        for(int i=0;i<4;++i)
        {
            tile[i]=vector<int>(4,0);
            for(int j=0;j<4;++j)
                tile[i][j]=copy.tile[i][j];
        }
    }
    void inputTile()
    {
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j)
            {
                int n;
                cin>>n;
                tile[i][j]=n;
            }
    }
    /*
    void showState() const
    {
        for(int y=0;y<4;++y)
        {
            for(int x=0;x<4;++x)
                cout<<tile[y][x]<<' ';
            cout<<endl;
        }
        cout<<"---------------"<<endl;
    }*/
    // type =1 : 행 오른쪽으로 이동, =2 열 아래로 이동
    // pos번째 인덱스의 이동
    State moveTile(int type, int pos, int count)
    {
        while(count--)
        {
            for(int i=3;i>0;--i)
            {
                if(type==1)
                    swap(tile[pos][i], tile[pos][i-1]);
                else if(type==2)
                    swap(tile[i][pos], tile[i-1][pos]);
            }
        }
        return *this;
    }
    vector<State> getAdjacent() const
    {
        vector<State> adjacent;
        adjacent.reserve(24);
        for(int type=1;type<=2;++type)
            for(int pos=0;pos<4;++pos)
                for(int count=1;count<=3;++count)
                {
                    State copy(*this);
                    adjacent.push_back(copy.moveTile(type,pos,count));
                }
        return adjacent;
    }
    // map의 find가 이진 탐색 중 쓰일 연산자
    bool operator<(const State& rhs) const
    {
        int thisNum=0, rhsNum=0;
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j)
            {
                thisNum+=(i*4+j)*tile[i][j];
                rhsNum+=(i*4+j)*rhs.tile[i][j];
            }
        return thisNum<rhsNum;
    }
    bool operator==(const State& rhs) const
    {
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j)
                if(tile[i][j]!=rhs.tile[i][j])
                    return false;
        return true;
    }
};

int sgn(int x) 
{
    if(!x) 
        return 0;
    return x>0 ? 1 : -1;
}

int incr(int x)
{
    if(x<0)
        return x-1;
    return x+1;
}

int bidirectional(State start, State finish)
{
    map<State, int> c;
    queue<State> q;
    if(start==finish)
        return 0;
    q.push(start); c[start]=1;
    q.push(finish); c[finish]=-1;
    while(!q.empty())
    {
        State here=q.front();
        q.pop();
        vector<State> adjacent=here.getAdjacent();
        for(int i=0;i<adjacent.size();++i)
        {
            map<State,int>::iterator it=c.find(adjacent[i]);
            if(it==c.end())
            {
                c[adjacent[i]]=incr(c[here]);
                q.push(adjacent[i]);
            }
            else if(sgn(it->second) != sgn(c[here]))
                return abs(it->second)+abs(c[here])-1;
        }
    }
    return -1;
}

int main()
{
    State start, finish;
    start.inputTile();
    vector<State> s=start.getAdjacent();
    
    cout<<bidirectional(start,finish);
    
    return 0;
}
