# 해결 
오름차순으로 출력해야 하기 때문에 2부터 계속해서 나누다가 더 이상 나눠지지 않으면 3을 나누는 방식으로 나아간다.  
그러다 sqrt(n)에 도달한 경우 더 이상 나눠지지 않으므로 마지막 수를 출력한다.  
```c++
void printResult(int n)
{
    for(int i=2;i*i<=n;++i)
        while(n%i==0)
        {
            n/=i;
            cout<<i<<endl;
        }
    if(n>1)
        cout<<n<<endl;
}
```
# 회고 
마지막 조건문을 넣지 않았을 때 계속 오답이 나오는데 이유를 알 수 없다.  
```c++
//틀린 함수
void printResult(int n)
{
    if(n==1)
    {
        cout<<1;
        return;
    }
    
    while(n!=1)
    {
        for(int i=2;i<=n;++i)
            if(n%i==0)
            {
                n/=i;
                cout<<i<<endl;
                break;
            }
    }
}
```
