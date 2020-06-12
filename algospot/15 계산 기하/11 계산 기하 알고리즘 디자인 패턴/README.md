# 계산 기하 알고리즘 디자인 패턴 
## 평면 스위핑(plane sweeping) 
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
