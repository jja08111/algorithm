# 해결 
대출금을 실수단위로 받는 것을 보면 마냥 공식으로 계산했을 때 오차가 발생할 수 있다.  
이를 막기 위해 이분법을 이용하여 오차를 최소화 할 수 있다.  
- 한 달에 monthlyPayment로 갚았을 경우의 잔금을 반환하는 balance 함수를 만드는 것이 중요하다. 
- 불변 조건을 눈여겨 봐야한다. 
```c++
// amount원을 연 이율 rates퍼센트로 duration월 간 한 달에 monthlyPayment로
// 남았을 때 대출 잔금은?
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
```
