#include <iostream>
using namespace std;

int n,need,sum;
int usingMemory[100], refreshCost[100], c[10000];

// (c[리프레시 비용]=최대 메모리 사용량)을 계산한다.
void calcMemory(void)
{
    for(int idx=0;idx<n;++idx)
        for(int cost=sum; cost>=refreshCost[idx]; --cost)
            c[cost]=max(c[cost],c[cost-refreshCost[idx]]+usingMemory[idx]);
}

int getMinCost(void)
{
    for(int i=0;i<sum;++i)
        if(c[i]>=need)
            return i;
}

int main(void)
{
    cin>>n>>need;
    for(int i=0;i<n;++i)
        cin>>usingMemory[i];
    sum=0;
    for(int i=0;i<n;++i)
    {
        cin>>refreshCost[i];
        sum+=refreshCost[i];
    }
    
    calcMemory();
    cout<<getMinCost();

    return 0;
}
