#include <iostream>
#include <cstring>
using namespace std;

const int MOD=1000000007;

int cache[101];

int tiling(int n)
{
    //이렇게 해야 초기n값이 2인 경우를 해결할수있다.
    if(n<=1)
        return 1;
    
    int& ret=cache[n];
    if(ret!=-1)
        return ret;
    
    return ret=(tiling(n-2)+tiling(n-1))%MOD;
}

int solve(int n)
{
    //모듈러 연산시 빼기 연산을 눈여겨 볼 필요가 있다.
    if(n%2)
        return (tiling(n)-tiling(n/2)+MOD)%MOD;
    
    int ret=tiling(n);
    ret=(ret-tiling(n/2)+MOD)%MOD;
    ret=(ret-tiling(n/2-1)+MOD)%MOD;
    return ret;
}

int main(void)
{
    int testCase;
    
    cin>>testCase;
    
    while(testCase--)
    {
        int n; cin>>n;
        
        memset(cache,-1,sizeof(cache));
        
        cout<<solve(n)<<endl;
    }
    
    return 0;
}
