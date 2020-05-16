# 해결
이 문제는 기하 문제이다.  
따라서 적절하게 다루기 쉬운 꼴로 변형하여야 한다.  
### 1. 중심각으로 표현
그 중 초소가 감시할 수 있는 범위와 위치를 중심각으로 표현하는 것이다.  
중심각이 모두 덮히면 그때 완벽하게 감시할 수 있다는 것이다.  

초소 감시범위의 중심각을 현재위치인 location과 감시범위 반지름에 대한 부채꼴의 중심각 range를 이용하여 구할 수 있다.  

- location을 함수 atan2를 이용하여 쉽게 구할 수 있다.  
atan2는 점 P=(y,x)를 입력 받아 x축의 양의 방향과 선분OP 사이의 각도를 [-π,π]구간 내의 값으로 반환한다.  
따라서 location=atan2(y,x)이다.  
- 초소의 중심, 초소의 감시범위와 성벽의 접점, 성벽의 중심을 꼭짓점으로 하는 이등변삼각형이 있다고 하자.  
삼각형을 반으로 나누면 직각삼각형이 나오는데 직각삼각형의 빗변(=8)과 높이(=r/2)를 알고 있으니 asin을 이용하여 θ를 구할 수 있다.  
따라서 range=2xasin(radius/2/8)이다.  
range를 정규화 하지 않은 이유는 아래 2번 항목 때문이다.

실수 값을 fmod()를 이용하여 범위를 제한할 수 있다.  
```c++
const double PI=2.0*acos(0);
void convertToRange()
{
    for(int i=0;i<n;++i)
    {
        double location=fmod(2*PI+atan2(yPos[i],xPos[i]),2*PI);
        //초소의 중심, 감시범위와 성벽이 만나는곳, 성벽의 중심을 꼭짓점으로 하는
        //삼각형을 이용하여 각을 구한다.
        double range=2.0*asin(radius[i]/2.0/8.0);
        ranges[i]=make_pair(location-range,location+range);
    }
    sort(ranges,ranges+n);
}
```

### 2. 원을 잘라 선분으로 만들기
원을 중심각 0인 지점에서 끊어서 선분으로 피면 문제를 풀기 수월하다.  
하지만 감시범위가 중심각 0인 부분을 포함하는 초소를 해결해야 한다.  
- 이 부분은 0을 덮는 구간을 하나하나 시도해 보고 최소의 답을 반환한다.  
그 후 0을 덮는 구간들을 뺀 구간에서 결과를 구하고 1개의 초소를 추가하면 답이 된다.  
- 시작위치와 끝위치를 정규화해야 한다.  
정규화 하지 않으면 시작위치가 끝위치보다 커버릴 수 있다.  
```c++
int solveCircular()
{
    int ret=INF;
    sort(ranges,ranges+n);
    for(int i=0;i<n;++i)
        if(ranges[i].first<=0 || ranges[i].second>=2*PI)
        {
            double begin=fmod(ranges[i].second, 2*PI);
            double end=fmod(ranges[i].first+2*PI, 2*PI);
            ret=min(ret, 1+solveLinear(begin, end));
        }
    return ret;
}
```
### 3. 마무리 
각 구간이 시작위치가 빠른 순서대로 정렬되어 있다는 것이 중요하다.  
그래야 한바퀴만 돌면 끝나기 때문이다.  
```c++
int solveLinear(double begin, double end)
{
    int used=0, idx=0;
    while(begin<end)
    {
        //begin과 겹치는 구간 중 가장 늦게 끝나는 구간을 찾는다.
        double maxCover=-1;
        while(idx<n && ranges[idx].first<=begin)
        {
            maxCover=max(maxCover,ranges[idx].second);
            ++idx;
        }
        //덮을 구간을 찾지 못한 경우
        if(maxCover<=begin)
            return INF;
        begin=maxCover;
        ++used;
    }
    return used;
}
```
