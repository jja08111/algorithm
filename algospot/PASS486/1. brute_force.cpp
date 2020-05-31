#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAX_N=10000001;
int factorsNum[MAX_N];

void getFactorsNum()
{
    memset(factorsNum,0,sizeof(factorsNum));
    for(int divide=1;divide<MAX_N;++divide)
        for(int multiple=divide;multiple<MAX_N;multiple+=divide)
            ++factorsNum[multiple];
}

int solve(int n, int lo, int hi)
{
    int ret=0;
    for(int i=lo;i<=hi;++i)
        if(n==factorsNum[i])
            ++ret;
    return ret;
}

int main()
{
    int testCase;
    cin>>testCase;
    
    getFactorsNum();
    while(testCase--)
    {
        int n,lo,hi;
        cin>>n>>lo>>hi;
        cout<<solve(n,lo,hi)<<endl;
    }
    return 0;
}
