#include <iostream>
using namespace std;

const int INF=987654321;
int n,num[11];
//순서:[0]plus,[1]minus,[2]multiply,[3]divide
int operationsNum[4];

void init(void)
{
    cin>>n;
    for(int i=0;i<n;++i)
        cin>>num[i];
    for(int i=0;i<4;++i)
        cin>>operationsNum[i];
}

int calcUsingOperator(int frontRet, int index, int operatorIdx)
{
    int ret;
    switch(operatorIdx)
    {
        case 0: ret=frontRet+num[index]; break;
        case 1: ret=frontRet-num[index]; break;
        case 2: ret=frontRet*num[index]; break;
        case 3: ret=frontRet/num[index]; break;
    }
    return ret;
}

int getMaxOrMinRet(int begin, bool needMax)
{
    if(begin==0)
        return num[begin];
    
    int ret=INF*(needMax ? -1 : 1);
    for(int i=0;i<4;++i)
        if(operationsNum[i]>0)
        {
            --operationsNum[i];
            int candidate=calcUsingOperator(getMaxOrMinRet(begin-1,needMax),begin,i);
            ret=needMax ? max(ret,candidate) : min(ret,candidate);
            ++operationsNum[i];
        }
    
    return ret;
}

int main(void)
{
    init();
    
    cout<<getMaxOrMinRet(n-1,true)<<endl<<getMaxOrMinRet(n-1,false);
}
