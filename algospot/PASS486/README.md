# 해결 
숫자 n의 약수의 개수를 1부터 시작해서 sqrt(n)까지 하나하나 약수인지 확인하는 방법이 있다.  
하지만 이 방법은 문제를 해결하기에는 너무 느리다.  

다른 방법으로는 소인수 분해한 결과를 이용하여 약수의 수를 구하는 것다.  
예를 들어 486의 소인수 분해 결과는 2 x 3^5이다.  
그렇다면 486의 약수의 수는 (1+1)x(5+1)=12이다.  
위와같은 방법을 이용하여 약수의 수를 구할 수 있다.  

### 에라토스테네스의 체를 이용한 소인수 분해  
에라토스테네스의 소수를 구하는 방법을 응용해 각 수에 대한 가장 작은 소인수를 구할 수 있다.  
이 내용은 "14.2소수" 폴더에 정리되어 있다.  
```c++
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
```

위 처럼 가장 작은 소인수를 구한 다음 아래와 같은 방식으로 약수의 개수를 구할 수 있다.  
- 소수인 경우 약수가 두 개 밖에 없으니 예외로 처리한다.  
- 소수가 아닌 경우, 현재 수(n)을 가장 작은 소인수로 나눈 수의 약수의 수를 이용해 n의 약수를 찾는다.  
    - 예를 들어 67,500의 약수를 찾기 위해 최소약수인 2로 나누어 33,750 = 2 x 3^3 x 5^4 를 얻을 수 있는데,   
    여기서 2가 1개인데 2개로 바꾸면 67,500이 되는 것 처럼 33,750의 약수의 수에서 3/2를 곱하면 답을 구할 수 있다.   
```c++
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
```

### 단순한 방법 
에라토스테네스의 체를 이용하지 않고 약수를 직접 구할 수도 있으나 이 방법은 2.5배 느리다.  
```c++
void getFactorsNum()
{
    memset(factorsNum,0,sizeof(factorsNum));
    for(int divide=1;divide<MAX_N;++divide)
        for(int multiple=divide;multiple<MAX_N;multiple+=divide)
            ++factorsNum[multiple];
}
```
