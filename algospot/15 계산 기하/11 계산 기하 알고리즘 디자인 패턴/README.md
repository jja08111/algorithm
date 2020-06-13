# 계산 기하 알고리즘 디자인 패턴 
## 1. 평면 스위핑(plane sweeping) 
이 기법을 이용하는 알고리즘은 수평선 혹은 수직선으로 평면을 **쓸고 지나가면서** 문제를 해결한다.  
### 직사각형 합집합의 면적  
여러개의 직사각형이 주어질 때 이들의 합집합의 면적을 구하려면 평면 스위핑 알고리즘이 제격이다.  

방법은 먼저 모든 직사각형을 겹치고 난 도형을 y축과 수평이 되는 직선이 x축의 양의 방향으로 지난다고 생각하자.  
이때 직선으로 잘린 선분의 길이가 변하는 부분이 있을 것이다.  
이 부분의 위치를 이벤트(event)라고 부르자.  
이벤트의 위치와 도형의 세로선의 길이가 얼마인지 안다면 이벤트 사이의 길이와 세로선의 길이를 곱한 값들을 전부 더해서 도형의 넓이를 구할 수 있다.  

y좌표의 집합들을 만들어서 현재 이벤트에서 몇개의 사각형이 겹쳐있는지 count를 갱신한다.   
이때 사각형이 시작하는 이벤트일때 delta를 1, 끝날때 -1로 설정한 부분을 볼 수 있다.  

사각형이 겹쳐져 있는 부분들의 ys[i+1]-ys[i], 즉 길이를 더해서 겹친 도형의 세로길이를 구한다.  
```c++
struct Rectangle {
    int x1,y2,x2,y2;
};

int unionArea(const vector<Rectangle>& rects) 
{
    if(rects.empty()) 
        return 0;
    
    //이벤트 정보: (x좌표, 왼쪽인가 오른쪽인가, 사각형의 번호)
    typedef pair<int,pair<int,int> > Event;
    vector<Event> events;
    vector<int> ys;
    
    //각 사각형을 순회하면서 y좌표의 모음과 이벤트의 집합을 찾는다.
    for(int i=0;i<rects.size();++i)
    {
        ys.push_back(rects[i].y1);
        ys.push_back(rects[i].y2);
        events.push_back(Event(rects[i].x1, make_pair(1,i)));
        events.push_back(Event(rects[i].x2, make_pair(-1,i)));
    }
    //y 좌표의 집합을 정렬하고 중복을 제거
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(),ys.end()), ys.end());
    //이벤트 목록을 정렬
    sort(events.begin(), events.end());
    
    int ret=0;
    //count[i]=ys[i]~ys[i+1] 구간에 겹쳐진 사각형의 수
    vector<int> count(ys.size()-1,0);
    for(int i=0;i<events.size();++i)
    {
        int x=events[i].first, delta=events[i].second.first;
        int rectangle=events[i].second.second;
        //count[]를 갱신
        int y1=rects[rectangle].y1, y2=rects[rectangle].y2;
        for(int j=0;j<ys.size();++j)
            if(y1<=ys[j] && ys[j]<y2)
                count[j]+=delta;
        //cutLength()값을 계산한다.
        int cutLength=0;
        for(int j=0;j<ys.size()-1;++j)
            if(count[j]>0)
                cutLength+=ys[j+1]-ys[j];
        //다음 이벤트까지의 거리에 cutLength를 곱한 값을 ret에 더한다.
        if(i+1 < events.size())
            ret+=cutLength*(events[i+1].first-x);
    }
    return ret;
}
```

## 2. 회전하는 캘리퍼스(Rotating Calipers)
[캘리퍼스](https://ko.wikipedia.org/wiki/%EC%BA%98%EB%A6%AC%ED%8D%BC%EC%8A%A4)가 무언가를 재는 과정을 알고리즘으로 만든 것이다.  
### 볼록 다각형의 지름 
단순히 모든 쌍을 순회하며 볼록 다각형에 완전히 포함되는 가장 긴 선분의 길이를 구할 수 있다.  
하지만 이 방법은 점의 수 N에 대해 O(N²) 시간 복잡도를 가지게 되어 너무 느리다.  

여기서 캘리퍼스를 통해 볼록 다각형의 지름을 재는 것 처럼 알고리즘을 구현하여 복잡도를 향상 시킬 수 있다.  
요약한 순서는 아래와 같다.  
1. 가장 왼쪽점 a와 오른쪽 점 b를 찾는다.
2. x축과 수직이 되는 방향 벡터를 설정한다.  
3. a와 b중 다음 점과의 연결되는 벡터와 현재의 벡터의 각도가 작은 점을 먼저 시도한다.  
4. 반 바퀴 돌아 두 벡터가 서로 바뀔 때까지 반복한다.  

여기서 유의해서 볼 부분은 다음과 같다.  
- 두 벡터의 방향은 항상 반대이기 때문에 첫 번째 직선의 벡터만 저장한다.
- 현재 점에서 다음 점까지의 방향을 나타내는 단위 벡터를 미리 초기화 한다.
- 구간 [0,π] 까지의 코사인 값은 계속 감소하는 점을 이용해 각도를 구하지 않고 내적한 값을 바로 이용하였다.  
```c++
// 시계 반대 방향으로 주어진 볼록 다각형에서 가장 먼 꼭지점 쌍 사이의 거리를 반환한다.
double diameter(const polygon& p)
{
    int n=p.size();
    // 우선 가장 왼쪽에 있는 점과 오른쪽에 있는 점을 찾는다.
    int left=min_element(p.begin(),p.end())-p.begin();
    int right=max_element(p.begin(),p.end())-p.begin();
    // p[left]와 p[right]에 각각 수직선을 붙인다. 두 수직선은 서로 정반대 방향을 가리키므로,
    // A의 방향만을 표현하면 된다.
    vector2 calipersA(0,1);
    double ret=(p[right]-p[left]).norm();
    
    // toNext[i]=p[i]에서 다음 점까지의 방향을 나타내는 단위 벡터
    vector<vector2> toNext(n);
    for(int i=0;i<n;++i)
        toNext[i]=(p[(i+1)%n]-p[i]).normalize();
    
    // a와 b는 각각 두 선분이 어디에 붙은 채로 회전하고 있는지를 나타낸다.
    int a=left, b=right;
    // 반 바퀴 돌아서 두 선분이 서로 위치를 바꿀 때까지 계속한다.
    while(a!=right || b!=left)
    {
        // a에서 다음 점까지의 각도와 b에서 다음 점까지의 각도 중 어느 쪽이 작은지 확인
        double cosThetaA=calipersA.dot(toNext[a]);
        double cosThetaB=-calipersA.dot(toNext[b]);
        if(cosThetaA>cosThetaB) //thetaA < thetaB
        {
            calipersA=toNext[a];
            a=(a+1)%n;
        }
        else
        {
            calipersA=toNext[b];
            b=(b+1)%n;
        }
        ret=max(ret,(p[a]-p[b]).norm());
    }
    return ret;
}
```
