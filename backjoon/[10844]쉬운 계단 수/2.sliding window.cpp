#include <iostream>
#include <cstring>
using namespace std;

const int MOD=1000000000;

int countStepNum(int digit)
{
    // c[자릿수][현재 수]
    // c의 index={-1,0,1,2,~~,9,10} 라고 생각하면 이해하기 쉽다.
    int c[2][12]={0,};
    
    for(int j=2;j<11;++j)
        c[1][j]=1;
    
    for(int i=2;i<=digit;++i)
        for(int j=1;j<11;++j)
            c[i%2][j]=(c[(i-1)%2][j-1]+c[(i-1)%2][j+1])%MOD;
    
    int ret=0;
    for(int j=1;j<11;++j)
        ret=(ret+c[digit%2][j])%MOD;
    
    return ret;
}

int main(void)
{
    int n;
    cin>>n;
    
    cout<<countStepNum(n)<<endl;
    
    return 0;
}
