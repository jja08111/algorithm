#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

class State 
{
private:
    vector<int> tile[4];
public:
    State(bool isStart)
    {
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j)
            {
                if(isStart)
                {
                    int n;
                    cin>>n;
                    tile[i].push_back(n);
                }
                else
                    tile[i].push_back(4*i+j+1);
            }
    }
    // 복사 생성자
    State(const State& copy)
    {
        for(int i=0;i<4;++i)
        {
            copy.tile[i]=vector<int>(4,0);
            for(int j=0;j<4;++j)
                copy.tile[i][j]=tile[i][j];
        }
    }
    // type =1 : 행 오른쪽으로 이동, =2 열 아래로 이동
    // pos번째 인덱스의 이동
    State moveTile(int type, int pos, int count)
    {
        while(count--)
            for(int i=3;i>0;--i)
                if(type==1)
                    swap(tile[pos][i], tile[pos][i-1]);
                else
                    swap(tile[i][pos], tile[i-1][pos]);
        return *this;
    }
    vector<State> getAdjacent() const
    {
        vector<State> adjacent;
        for(int type=1;type<=2;++type)
            for(int pos=0;pos<4;++pos)
                for(int count=1;count<=3;++count)
                {
                    State copy(*this);
                    adjacent.push_back(copy.moveTile(type,pos,count));
                }
        return adjacent;
    }
    bool operator<(const State& rhs) const;
    bool operator==(const State& rhs) const;
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
    State start(true);
    
    
    
    return 0;
}
