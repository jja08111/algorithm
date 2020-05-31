#include <iostream>
using namespace std;

// amount원을 연 이율 rates퍼센트로 duration월 간 한 달에 monthlyPayment로
// 남았을 떄 대출 잔금은?
double balance(double amount, int duration, double rates, double monthlyPayment)
{
    double ret=amount;
    for(int i=0;i<duration;++i)
    {
        ret*=(1.0+(rates/12.0)/100.0);
        ret-=monthlyPayment;
    }
    return ret;
}

// amount원을 연 이율 rates퍼센트로 duration월 간 갚으려면 한달에 얼마씩 갚아야 하나?
double payment(double amount, int duration, double rates)
{
    // 불변 조건: 
    // 1. lo원씩 갚으면 duration개월 안에 갚을 수 없다.
    // 2. hi원씩 갚으면 duration개월 안에 갚을 수 있다.
    double lo=0, hi=amount*(1.0+(rates/12.0)/100.0);
    for(int iter=0;iter<100;++iter)
    {
        double mid=(lo+hi)/2.0;
        if(balance(amount,duration,rates,mid)<=0)
            hi=mid;
        else
            lo=mid;
    }
    return hi;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        double amount, rates;
        int duration;
        cin>>amount>>duration>>rates;
        
        printf("%.10lf \n",payment(amount,duration,rates));
    }
    return 0;
}
