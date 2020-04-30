#include <iostream>
#include <cstring>
using namespace std;

//범위를 2003까지 한 이유는 day가 0일때 확률 계산이 끝나기 때문이다.
double cache[2003][1001];
int n,m;

double solve(int dep, int day)
{
    if(day==m)
        return dep>=n ? 1.0 : 0.0;
    
    double& ret=cache[dep][day];
    if(ret>-0.5)
        return ret;
    
    return ret=0.75*solve(dep+2,day+1)+0.25*solve(dep+1,day+1);
}

int main(void)
{
    int testCase;
    
    cin>>testCase;

    while(testCase--)
    {
        cin>>n>>m;
        
        for(int i=0;i<n*2+1;++i)
            memset(cache[i],-1,sizeof(double)*m);
        
        printf("%.10lf\n",solve(0, 0));
    }
    
    return 0;
}
