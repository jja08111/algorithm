# 해결 
이 문제를 최적화 문제와 결정 문제로 형태를 표현할 수 있다.
- 카메라 간 최소 간격의 최대치를 반환한다.
- 카메라를 적당히 배치해 일정 간격 이상이 되도록 하는 방법이 있는가?

여기서는 후자의 방법으로 해결해 보겠다.

### 질문을 어떻게 하느냐에 따라 다르다.
**"카메라를 적당히 배치해 일정 간격이 되는 방법이 있는가?"** 라고 질문 하지 않고 
**"카메라를 적당히 배치해 일정 간격 이상이 되도록 하는 방법이 있는가?"** 라고 질문하는 이유는 이분법을 사용할 것이기 때문이다.  
이분법을 이용하여 간격 gap의 [lo,hi]구간에서 중앙인 mid가 가능하다면 반으로 쪼개서 [mid,hi]로 계속하다 보면 답을 찾을 수 있다.  
```c++
//결정 문제: 정렬되어 있는 locations중 cameras를 선택해 모든 카메라 간의 간격이
//gap이상이 되는 방법이 있는지를 반환한다.
bool decision(const vector<double>& location, int cameras, double gap)
{
    double limit=-1;
    int installed=0;
    for(int i=0;i<location.size();++i)
        if(limit<=location[i])
        {
            ++installed;
            //location에서 gap만큼 떨어져야 카메라를 설치할 수 있다.
            limit=location[i]+gap;
        }
    //cameras대 이상을 설치할 수 있으면 성공
    return installed>=cameras;
}

double optimize(const vector<double>& location, int cameras)
{
    double lo=0, hi=241;
    //반복문 불변식: decision(lo) && !decision(hi)
    for(int it=0;it<100;++it)
    {
        double mid=(lo+hi)/2.0;
        //mid만큼 간격을 벌려도 설치 가능하면 답은 [mid,hi]에 있다.
        if(decision(location,cameras,mid))
            lo=mid;
        else
            hi=mid;
    }
    return lo;
}
```
