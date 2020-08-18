#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX_DISCS=12;

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

// index원판이 어느 기둥에 들어있는지 반환
int get(int state, int index)
{
    return (state >> (index*2)) & 3;
}
// 현재 있던 index 원반을 제거 후, value 위치에 원반을 놓음
int set(int state, int index, int value)
{
    return (state & ~(3<<(index*2))) | (value << (index*2));
}

int c[1<<(MAX_DISCS*2)];

int bidir(int discs, int begin, int end)
{
    if(begin==end)
        return 0;
    
    queue<int> q;
    // 초기화를 0으로 하는 데 주의
    memset(c,0,sizeof(c));
    q.push(begin); c[begin]=1;
    q.push(end); c[end]=-1;
    
    while(!q.empty())
    {
        int here=q.front();
        q.pop();
        
        // 각 기둥의 맨 위에 어떤 원반이 있는지 계산한다.
        int top[4]={-1,-1,-1,-1};
        for(int i=discs-1;i>=0;--i)
            top[get(here,i)]=i;
        
        // i번 기둥 맨 위에 있는 원반을 j번 기둥으로 옮긴다.
        for(int i=0;i<4;++i)
            if(top[i]!=-1)
                for(int j=0;j<4;++j)
                    if(i!=j && (top[j]==-1 || top[j]>top[i]))
                    {
                        int there=set(here,top[i],j);
                        if(c[there]==0)
                        {
                            c[there]=incr(c[here]);
                            q.push(there);
                        }
                        else if(sgn(c[here])!=sgn(c[there]))
                            return abs(c[here])+abs(c[there])-1;
                    }
    }
    return -1;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int diskNum;
        int begin=0, end=0;
        cin>>diskNum;
        for(int i=0;i<4;++i)
        {
            int diskNumInTower;
            cin>>diskNumInTower;
            for(int j=0;j<diskNumInTower;++j)
            {
                int diskIndex;
                cin>>diskIndex;
                // 0번 ~ diskIndex-1 번으로 표현
                begin=set(begin,diskIndex-1,i);
            }
        }
        for(int j=0;j<diskNum;++j)
            end=set(end,j,3);
        
        cout<<bidir(diskNum,begin,end)<<endl;
    }
    
    return 0;
}
