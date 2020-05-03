#include <iostream>
#include <cstring>
using namespace std;

const int INF=987654321;
int n,start,dist[16][16];
int cache[16][1<<16];

void init(void)
{
    cin>>n;
    memset(cache,-1,sizeof(cache));
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            cin>>dist[i][j];
}

int getMinCost(int here, int visited)
{
    if((1<<n)-1==visited)
    {
        if(dist[here][0]!=0)
            return dist[here][0];
        return INF;
    }
    
    int& ret=cache[here][visited];
    if(ret!=-1)
        return ret;
    
    ret=INF;
    for(int next=0;next<n;++next)
        // 길이 없을 수도 있다.
        if((visited & (1<<next))==0 && dist[here][next]!=0)
            ret=min(ret,dist[here][next]+getMinCost(next,visited+(1<<next)));
    
    return ret;
}

int main(void)
{
    init();
    
    //첫위치로 다시 돌아오게 되므로 첫위치만 탐색해도 결과가 나온다.
    cout<<getMinCost(0,1)<<endl;
}
