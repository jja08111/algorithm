# 소수(prime number) 
### 1. 간단한 소수 판별 알고리즘 
주어진 수 n이 소수인지를 판단하는 간단한 방법 아래와 같다.  
sqrt(n)이상의 수로 n을 나누었을때는 중복되어 의미가 없다.  
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
### 3. 에아토스테네스의 체
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
