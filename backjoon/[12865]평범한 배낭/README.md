# 해결
### 재귀함수 이용
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
### 반복문 이용
점화식을 이용하여 반복문을 통해 구현할 수 있다.  
이를 이용하면 속도와 공간 모두 잡을 수 있다.
```c++
for (int j = k; j >= w; j--) {
	dp[j] = max(dp[j], dp[j - w]+v);
}
```

# 회고
기저사례를 remain이 0이었을때로 잘못 설정해 런타임에러를 만들었다.  
남은 무게보다 현재 가방의 무게가 높으면 고르지 않기 때문에 기저사례가 here==n이라는 것을 생각하게 되었다. 
