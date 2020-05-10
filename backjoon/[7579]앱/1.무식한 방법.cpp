#include <iostream>
using namespace std;

int n, limit;
int usingMemory[101], refreshCost[101], c[10000000]={0,};

int getMaxCost(void)
{
    for(int idx=0;idx<n;++idx)
        //증가(++)로 구현하면 중복해서 갯수를 센다.
        for(int memory=limit; memory>=usingMemory[idx]; --memory)
            c[memory]=max(c[memory],c[memory-usingMemory[idx]]+refreshCost[idx]);
    
    return c[limit];
}

int main(void)
{
    int need;
    cin>>n>>need;
    
    int sumUsingMemory=0, sumRefreshCost=0;
    for(int i=0;i<n;++i)
    {
        cin>>usingMemory[i];
        sumUsingMemory+=usingMemory[i];
    }
    for(int i=0;i<n;++i)
    {
        cin>>refreshCost[i];
        sumRefreshCost+=refreshCost[i];
    }
    
    limit=sumUsingMemory-need;
    
    int ret=sumRefreshCost-getMaxCost();
    cout<<ret;

    return 0;
}
