# 해결
n개의 가방을 고르거나 고르지 않는 2가지의 경우의 수가 있다.

따라서 2^n경우를 고려하는 문제이다.

동적계획법을 이용하여 문제를 해결했다.

유의하며 볼 부분은 아래와 같다.
- 가방을 고르거나 고르지 않거나 
- 기저사례가 index가 n에 도달했을때
```c++
int getMaxValue(int here, int remain)
{
    if(here==n)
        return 0;
    
    int& ret=cache[here][remain];
    if(ret!=-1)
        return ret;
    
    ret=getMaxValue(here+1,remain);
    if(remain>=weight[here])
    {
        int candidate=value[here]+getMaxValue(here+1,remain-weight[here]);
        ret=max(ret,candidate);
    }
    return ret;
}
```
