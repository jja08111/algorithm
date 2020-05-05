#include <iostream>
using namespace std;

int map[101][101];
int cache[101][101];
int n;

void init(void)
{
    cin>>n;
    
    for(int y=0;y<n;++y)
        for(int x=0;x<y+1;++x)
        {
            cin>>map[y][x];
            cache[y][x]=-1;
        }
}

//전체 문제를 부분 문제로 나누어서 해결
int path(int y, int x)
{
    //기저사례:마지막 라인에 도달한 경우
    if(y==n-1)
        return map[y][x];
    
    int& ret=cache[y][x];
    if(ret!=-1)
        return ret;
    
    return ret=map[y][x]+max(path(y+1,x),path(y+1,x+1));
}

int main(void)
{
    int testCase;
    
    cin>>testCase;
    
    while(testCase--)
    {
        init();
        
        cout<<path(0,0)<<endl;
    }

    return 0;
}
