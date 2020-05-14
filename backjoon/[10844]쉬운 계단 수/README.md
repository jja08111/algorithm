# 해결
### 1. 재귀적 구현
이 문제를 접하면 바로 점화식을 만들 수 있을 것이다.  
기저사례를 자릿수가 1자리가 되었을 때로 설정하고 범위를 벗어나지 않는 것만 유의하면 쉽게 해결 할 수 있다.  
```c++
int countStepNum(int here, int digit)
{
    if(digit==1)
        return 1;
    
    int& ret=cache[here][digit];
    if(ret!=-1)
        return ret;
    
    ret=0;
    if(1<=here)
        ret=(ret+countStepNum(here-1,digit-1))%MOD;
    if(here<9)
        ret=(ret+countStepNum(here+1,digit-1))%MOD;
    
    return ret;
}
```

### 2. sliding window 기법 이용
먼저 재귀적으로 구현하지 않고 반복적으로 구현을 한다.  
그러면 배열이 현재 계단수를 계산하기 위해서 이전 계단수만 알면 된다는 사실을 알 수 있다.  
이러한 부분을 이용하여 공간 복잡도를 크게 줄일 수 있다.  

아래 코드에서 눈여겨 볼 것은 양 끝의 범위 설정한 부분이다.  
1칸씩 좌우로 넓게 설정하여 구현을 간소화 할 수 있었다.
```c++
int countStepNum(int digit)
{
    // c[자릿수][현재 수]
    // c의 index범위를 [-1,10] 라고 생각하면 이해하기 쉽다.
    int c[2][12]={0,};
    
    for(int j=2;j<11;++j)
        c[1][j]=1;
    
    for(int i=2;i<=digit;++i)
        for(int j=1;j<11;++j)
            c[i%2][j]=(c[(i-1)%2][j-1]+c[(i-1)%2][j+1])%MOD;
    
    int ret=0;
    for(int j=1;j<11;++j)
        ret=(ret+c[digit%2][j])%MOD;
    
    return ret;
}
```
