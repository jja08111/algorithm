# 해결
입력에 주어지는 k의 범위가 엄청 크다.  
따라서 **"K번째 표지판의 위치는 어디인가?"** 라는 질문을 아래와 같이 바꿀 필요가 있다.  
- decision(x) = 시작점부터 x미터 지점까지 가면서 K개 이상의 표지판을 만날 수 있는가?  

이를 이분법으로 이용하여 간단하게 구현할 수 있다.  

### x지점까지의 표지판 개수 구하기  
i번째 표지판의 시작위치를 L-M=>start, 끝나는 위치를 L=>end, 표지판 사이의 간격을 g=>gap이라 하자.  
그러면 x지점 까지의 표지판 개수는 구간 [start,min(x,end)]의 길이를 gap으로 나눈 값에 1을 더하면 구할 수 있다.
```c++
struct RoadSign {
    int mStart, mEnd, mGap;
    void init(int l, int m, int g) {
        mStart=l-m;
        mEnd=l;
        mGap=g;
    }
    int count(int here) {
        //구간 [start, min(here,end)]에서 표지판의 개수 반환
        return (min(here,mEnd)-mStart)/mGap+1;
    }
};

int n, k;
vector<RoadSign> signs;

//dist 지점까지 가면서 표지판이 k개 이상인가?
bool decision(int dist)
{
    int sum=0;
    for(int i=0;i<n;++i)
        //표지판이 하나라도 존재할때
        if(dist>=signs[i].mStart)
        {
            sum+=signs[i].count(dist);
            if(sum>=k)
                return true;
        }
    return false;
}
```
