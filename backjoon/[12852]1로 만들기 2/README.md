# 해결 
시작은 전부를 탐색하는 것부터 나아간다.  
질문의 세 가지의 경우들을 전부 탐색하며 최소의 계산값을 찾는다.  
그리고 previous배열을 생성하여 최소값이 갱신되었을 때 이전 값들을 찾아나간다.  

하지만 완전 탐색은 시간내에 통과할 수 없다. 따라서 동적 계획법, 즉 DP를 이용하여 해결할 수 있다.  
현재 값 n에 대한 최적해를 cache에 저장해서 중복되는 계산들을 줄이는 방식이다.  
```c++
int solve(int n)
{
    if(n==1)
        return 0;
    
    int& ret=cache[n];
    if(ret!=-1)
        return ret;
    
    ret=INF;
    if(n%3==0)
    {
        ret=1+solve(n/3);
        previous[n]=n/3;
    }
    if(n%2==0)
    {
        int cand=1+solve(n/2);
        if(cand<ret)
        {
            ret=cand;
            previous[n]=n/2;
        }
    }
    int cand=1+solve(n-1);
    if(cand<ret)
    {
        ret=cand;
        previous[n]=n-1;
    }
    return ret;
}
```

최적해를 찾아가는 과정은 계산 과정에 형성된 previous의 값을 이용하면 된다.  
```c++
int idx=n;
while(true)
{
    cout<<idx<<' ';
    if(idx==1)
        break;
    idx=previous[idx];
}
```
