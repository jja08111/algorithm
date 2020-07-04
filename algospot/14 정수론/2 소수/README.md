# 소수(prime number) 
### 1. 간단한 소수 판별 알고리즘 
주어진 수 n이 소수인지를 판단하는 간단한 방법 아래와 같다.  
sqrt(n)이상의 수를 n으로 나누었을때는 중복되어 의미가 없다.  
따라서 1과 2를 예외로 처리하고 n이 구간 [3,sqrt(n)]안의 홀수로 나누어지지 않을때 소수라고 볼 수 있다.  
```c++
bool isPrime(int n) 
{
    if(n<=1)
        return false;
    if(n==2)
        return true;
    if(n%2==0)
        return false;
    int sqrtn=int(sqrt(n));
    
    for(int divide=3;divide<=sqrtn;divide+=2)
        if(n%divide==0)
            return false;
    return true;
}
```
### 2. 소인수 분해를 이용한 합성수를 소수들의 곱으로 표현 
2부터 시작해서 sqrt(n)까지 n의 약수를 찾을 때마다 n을 이 숫자로 나눈다.  
모든 정수를 시도하는 이유는 이미 앞에서 소인수들로 나눠진 뒤이기 때문에 divide가 합성수라면 n이 divide로 나눠질 수 없기 때문이다.  
```c++
vector<int> factorSimple(int n)
{
    vector<int> ret;
    int sqrtn=int(sqrt(n));
    
    for(int divide=2;divide<=sqrtn;++divide)
        while(n%divide==0)
        {
            n/=divide;
            ret.push_back(divide);
        }
    if(n>1)
        ret.push_back(n);
    return ret;
}
```
### 3. 에라토스테네스의 체
마치 체로 물건을 걸러내는 것처럼 2부터 n까지 현재 소수라고 판되는 수를 지워나가는 방식이다.  
여기서 최적화 할 것은 아래의 두가지이다. 
- 지워지지 않은 수를 찾을 때 sqrt(n)까지만 찾는다.  
- i의 배수들을 지울때 ixi에서 시작한다.  
왜냐하면 그 앞의 수들은 2xi, 3xi,... 에서 이미 지워졌기 때문이다.  
```c++
int n;
bool isPrime[MAX_N+1];

void eratosthenes()
{
    memset(isPrime,1,sizeof(isPrime));
    isPrime[0]=isPrime[1]=false;
    int sqrtn=int(sqrt(n));
    
    for(int i=2;i<=sqrtn;++i)
        if(isPrime[i])
            for(int j=i*i;j<=n;j+=i)
                isPrime[j]=false;
}
```
### 4. 에라토스테네스의 체를 이용한 빠른 소인수 분해 
최적화의 비결은 각 수가 소수인지만을 기록하지 않고 가장 작은 소인수를 기록하는 것이다.  
2부터 약수를 기록해나가면서 아직 약수가 나오지 않은 수에 현재 소수를 기록한다.  
그리고 다시 기록된 가장 작은 소인수들로 n을 나누며 소인수를 찾는다.  
```c++
int minFactor[MAX_N];

void eratosthenes2()
{
    minFactor[0]=minFactor[1]=-1;
    // 모든 숫자를 처음에는 소수로 표시해 둔다. 
    for(int i=2;i<=n;++i)
        minFactor[i]=i;
    int sqrtn=int(sqrt(n));
    
    for(int i=2;i<=sqrtn;++i)
    {
        if(minFactor[i]==i)
        {
            for(int j=i*i;j<=n;j+=i)
                //아직 약수를 본 적 없는 숫자인 경우 i를 써 둔다.
                if(minFactor[j]==j)
                    minFactor[j]=i;
        }
    }
}

vector<int> factor(int n)
{
    vector<int> ret;
    while(n>1)
    {
        ret.push_back(minFactor[n]);
        n/=minFactor[n];
    }
    return ret;
}
```
