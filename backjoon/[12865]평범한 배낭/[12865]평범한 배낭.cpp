#include <iostream>
#include <cstring>
using namespace std;

const int NAG_INF=-987654321;
int n,limit;
int weight[100],value[100];
//한도가 100000이니 index에 
int cache[101][100001];

void init(void)
{
    cin>>n>>limit;
    for(int i=0;i<n;++i)
        cin>>weight[i]>>value[i];
    memset(cache,-1,sizeof(cache));
}

int getMaxValue(int here, int remain)
{
    if(here==n)
        return 0;
    
    int& ret=cache[here][remain];
    if(ret!=-1)
        return ret;
    
    ret=getMaxValue(here+1,remain);
    if(remain>=weight[here])
    {
        int candidate=value[here]+getMaxValue(here+1,remain-weight[here]);
        ret=max(ret,candidate);
    }
    return ret;
}

int main(void)
{
    init();
    
    cout<<getMaxValue(0,limit);
    
    return 0;
}
