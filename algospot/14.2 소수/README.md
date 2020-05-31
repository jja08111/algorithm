# 소수(prime number) 판별 알고리즘 
### 1. 가장 단순한 방법 
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
