#include <iostream>
#include <cmath>
using namespace std;

const int TM=10*1000*1000;
// i의 가장 작은 소인수
int minFactor[TM+1];
// i의 소인수 분해에는 minFactor[i]의 몇 승이 포함되어 있는가?
int minFactorPower[TM+1];
// i가 가진 약수의 수
int factors[TM+1];

void eratosthenes2()
{
    minFactor[0]=minFactor[1]=-1;
    for(int i=2;i<=TM;++i)
        minFactor[i]=i;
    
    int sqrtn=int(sqrt(TM));
    for(int i=2;i<=sqrtn;++i)
    {
        if(minFactor[i]==i)
        {
            for(int j=i*i;j<=TM;j+=i)
                if(minFactor[j]==j)
                    minFactor[j]=i;
        }
    }
}

void getFactorsNum()
{
    factors[1]=1;
    for(int n=2;n<=TM;++n)
    {
        // 소수인 경우 약수가 두 개 밖에 없다.
        if(minFactor[n]==n)
        {
            minFactorPower[n]=1;
            factors[n]=2;
        }
        // 소수가 아닌 경우, 가장 작은 소인수로 나눈 수(m)의
        // 약수의 수를 응용해 n의 약수의 수를 찾는다.
        else
        {
            int p=minFactor[n];
            int m=n/p;
            // m이 p로 더이상 나누어지지 않는 경우
            if(p!=minFactor[m])
                minFactorPower[n]=1;
            else
                minFactorPower[n]=minFactorPower[m]+1;
            
            int a=minFactorPower[n];
            factors[n]=(factors[m]/a)*(a+1);
        }
    }
}

int main()
{
    int testCase;
    cin>>testCase;
    
    eratostenes2();
    getFactorsNum();
    while(testCase--)
    {
        int n,lo,hi;
        cin>>n>>lo>>hi;
        
        int ret=0;
        for(int i=lo;i<=hi;++i)
            if(factors[i]==n)
                ++ret;
        
        cout<<ret<<endl;
    }
    return 0;
}
