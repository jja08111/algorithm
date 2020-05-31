# 해결 
## 1. 이분법 이용 
최소한으로 연승해서 승률이 오르는 경기 수를 찾기 위해서 이분법을 이용했다.  
승률이 오르면 hi를 줄이고, 그대로면 lo를 증가시켰다.  
### 여기서 주의할 점은 중간 계산 과정에서 범위가 초과하기 때문에 꼭 long long형을 사용해야 하는 부분이다. 
```c++
const long long MAX_N=2000000000;

int winRatio(long long total, long long win)
{
    return win*100/total;
}

int neededGames(long long total, long long win)
{
    if(winRatio(total,win)==winRatio(total+MAX_N,win+MAX_N))
        return -1;
    
    long long lo=0, hi=MAX_N;
    int current=winRatio(total,win);
    while(lo+1<hi)
    {
        long long mid=(lo+hi)/2;
        int next=winRatio(total+mid,win+mid);
        if(next > current)
            hi=mid;
        else
            lo=mid;
    }
    
    return hi;
}
```

## 2. 수학적 해법 이용 
현재 N게임 중 M게임을 승리했고 목표하는 승률이 R이라고 하자.  
이때 승률 R이 되는 최소 연승 횟수 x는 다음과 같다.  
- 100(M+x)/(N+x) >= R

위의 식을 x에 대해 정리하면 아래처럼 된다.  
- x >= (RN-100M)/(100-R)

이 식을 만족하는 최소의 정수는 오른쪽 분수를 올림한 값이다.  
아래의 코드에서 올림한 부분을 눈여겨 볼 만 하다.  
```c++
int neededGames(long long total, long long win)
{
    long long ratio=getRatio(total,win)+1;
    
    if(ratio>=100)
        return -1;
    
    double ret=(double)(ratio*total-100*win)/(100-ratio);
    int temp=(int)ret;
    
    if(ret-(double)temp>0.0)
        return ret+1;
    return ret;
}
```
