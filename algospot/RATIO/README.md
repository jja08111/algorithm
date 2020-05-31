# 해결 
최소한으로 연승해서 승률이 오르는 경기 수를 찾기 위해서 이분법을 이용했다.  
승률이 오르면 경기수를 hi를 줄이고, 그대로면 lo를 증가시켰다.  
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
