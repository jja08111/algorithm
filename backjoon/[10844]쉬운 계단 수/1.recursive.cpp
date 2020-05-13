#include <iostream>
#include <cstring>
using namespace std;

const int MOD=1000000000;
//자릿수가 100까지 이니 101로 선언해야 한다.
int cache[10][101];

int countStepNum(int here, int digit)
{
    if(digit==1)
        return 1;
    
    int& ret=cache[here][digit];
    if(ret!=-1)
        return ret;
    
    ret=0;
    if(1<=here)
        ret=(ret+countStepNum(here-1,digit-1))%MOD;
    if(here<9)
        ret=(ret+countStepNum(here+1,digit-1))%MOD;
    
    return ret;
}

int main(void)
{
    int n;
    cin>>n;
    memset(cache,-1,sizeof(cache));
    
    int ret=0;
    for(int start=1;start<10;++start)
        ret=(ret+countStepNum(start,n))%MOD;
    
    cout<<ret<<endl;
    
    return 0;
}
