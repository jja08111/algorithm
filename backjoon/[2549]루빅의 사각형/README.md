# 해결 
이틀동안 군대에서 머리싸매며 사지방에서 푼 문제이다.  
원래 이 문제를 푸는 방법은 따로 있으나, 종만북을 공부하며 Bidirectional search(양방향 탐색)를 공부하던 중 이 문제를 보게 되어 양방향 탐색으로 풀어봤다.  
그래서 그런지 코드가 굉장히 길고 간결하지 않다.  
하지만 임무완수를 꼭 해낸다는 군인의 집념으로 어찌어찌 통과해낸 문제이다.  

양방향 탐색은 역방향 간선이 많지 않고 경로를 찾지 않는 문제가 적합한듯 하다.  

양방향 탐색이 까다로운 이유를 이 문제를 풀며 많이 깨달았다.  

먼저 이 문제는 경로를 형성해야 하기 때문에 적합하지 않았다.  
- 경로를 생성할때 정방향은 그대로 간선을 저장하면 되지만 역방향은 변환을 거쳐야 했다.
- 중간에서 만난 경우 정방향이 먼저 중간지점을 발견했는지 아닌지를 따로 구분해야 한다.  

경로를 출력하는 것도 문제이다.  
- 정방향 경로를 deque를 이용해 역으로 저장하고 그 다음 중간 간선을 넣고 역방향 경로를 넣는다.  

클래스를 이용했기 때문에(?) 간선의 값을 24미만의 값으로 저장한 후 변환을 거쳐 출력하는 방식을 택했다.  

# 회고 
- vector를 맴버 변수로 설정하니 계속 런타임 에러를 발생시켰다. 그래서 일반 배열로 선언했다.
- 복사 생성자를 선언해봤는데 기본 복사 생성자로 충분한 것 같아 제거했다.  
- map을 이용하려면 'operator <' 가 필요한데 이를 3번 넘게 잘못 정의하여 find가 제대로 작동하지 않았다.  
(이진 탐색시 연산자 '<'를 이용하는데 이를 잘못 정의했기 때문이다.)

```c++
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


```
