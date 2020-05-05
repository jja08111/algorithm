#include <iostream>
#include <cstring>
using namespace std;

const int INF=987654321;
int n,cost[1001][3];
int cache[1001][3];

void init(void)
{
    cin>>n;
    
    for(int i=0;i<n;++i)
        for(int j=0;j<3;++j)
            cin>>cost[i][j];
    memset(cache,-1,sizeof(cache));
}

int getMinSum(int here, int previousColor)
{
    if(here==n)
        return 0;
    
    int& ret=cache[here][previousColor];
    if(ret!=-1)
        return ret;
    
    ret=INF;
    for(int color=0;color<3;++color)
        // 첫번째 집이거나 앞의 집과 현재 집의 색상이 다를 
        if(here==0 || previousColor!=color)
            ret=min(ret,cost[here][color]+getMinSum(here+1,color));
    
    return ret;
}

int main(void)
{
    init();
    
    cout<<getMinSum(0,0);
    
    return 0;
}
