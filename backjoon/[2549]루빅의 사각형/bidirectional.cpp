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
// vector를 멤버로 가지면 안된다??
    int tile[4][4];
public:
    State()
    {
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j)
                tile[i][j]=4*i+j+1;
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
    // type=1 : 행 오른쪽으로 이동, =2 열 아래로 이동
    // pos번째 인덱스를 count번 이동
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
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j)
                if(tile[i][j]!=rhs.tile[i][j])
                    return tile[i][j]<rhs.tile[i][j];
        // 다르지 않다면 같다
        return false;
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

map<State,State> parent;
map<State,int> choice;
// 경로를 찾을 때 이용할 시작 정점
State front,back;
int midAdj;

// count번 이동하는 것을 변환하여 3번이면 1번, 1번이면 3번으로 바꾼다.
int convertReAdj(int n)
{
    int tmp=1-(n%12)%3;
    tmp*=2;
    return n+tmp;
}

int bidirectional(State start, State finish)
{
    map<State, int> c;
    queue<State> q;
    
    parent[start]=start;
    parent[finish]=finish;
    
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
            State& there=adjacent[i];
            map<State,int>::iterator it=c.find(there);
            if(it==c.end())
            {
                // 경로 형성
                parent[there]=here;
                // 방향이 반대인 경우 역으로 저장해야 한다.
                choice[there]=(c[here]>0) ? i : convertReAdj(i);
                
                c[there]=incr(c[here]);
                q.push(there);
            }
            // 양방향 탐색 도중 중간에서 만난 경우
            else if(sgn(it->second) != sgn(c[here]))
            {
                // 왼쪽에서 먼저 발견한 것을 오른쪽에서 탐색 중 발견한 경우 
                if((it->second)>0)
                {
                    midAdj=convertReAdj(i);
                    front=it->first;
                    back=here;
                }
                else
                {
                    midAdj=i;
                    front=here;
                    back=it->first;
                }
                return abs(it->second)+abs(c[here])-1;
            }
        }
    }
    return -1;
}

void printHowToMove()
{
    deque<int> route;
    
    // 앞 부분 경로 저장
    while(!(front==parent[front]))
    {
        route.push_front(choice[front]);
        front=parent[front];
    }
    // 중간과 뒷 부분 경로 저장
    route.push_back(midAdj);
    while(!(back==parent[back]))
    {
        route.push_back(choice[back]);
        back=parent[back];
    }
    
    for(int i=0;i<route.size();++i)
    {
        int n=route[i];
        if(n<12)
            cout<<1<<' ';
        else
        {
            cout<<2<<' ';
            n-=12;
        }
        cout<<(n/3)+1<<' '<<(n%3)+1<<endl;
    }
}

int main()
{
    State start, finish;
    start.inputTile();
    
    int ret=bidirectional(start,finish);
    cout<<ret<<endl;
    if(ret) printHowToMove();
    
    return 0;
}
