# 해결 
이 문제는 신발 사이즈와 타이핑 속도를 각각 x,y 좌표로 평면상에 나타내면  
너드와 너드가 아닌 집합을 나누는 직선을 찾는 문제로 변형할 수 있다.  

여기서 볼록 껍질(convex hull)을 이용하면 쉽게 해결 할 수 있다.   
두 개의 볼록 껍질이 서로 닿거나 겹치지 않는다면 둘 사이를 가로지르는 직선이 존재하기 때문이다.  
### 볼록 껍질 찾기  
볼록 껍질을 찾기 위해서 [선물 포장 알고리즘(Gift wrapping algorithm)](https://ko.wikipedia.org/wiki/%EC%84%A0%EB%AC%BC_%ED%8F%AC%EC%9E%A5_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98)을 이용할 수 있다.  
1. 가장 왼쪽아래의 기준점을 찾는다. 이 점은 항상 볼록 껍질에 포함된다.  
2. 이 점을 기준으로 가장 왼쪽에 있는 점을 찾는다.  
      - 기준점을 기준으로 현재까지 찾은 점 중 가장 왼쪽에 있는 점과 새로운 한점을 외적한다.   
      - 외적한 값이 양수이면 새로운 점이 더 기존에 찾은 점보다 왼쪽에 있는 것이니 교체한다.  
3. 점들이 일직선상에 있을 경우 더 먼 점을 선택한다.  
4. 기준점으로 돌아오면 종료한다.   
```c++
//points에 있는 점들을 모두 포함하는 최소의 볼록 다각형을 찾는다.
polygon giftWrap(const polygon& points)
{
    int n=points.size();
    polygon hull;
    //가장 왼쪽 아래 점을 찾는다. 이 점은 껍질에 반드시 포함된다.
    vector2 pivot=*min_element(points.begin(), points.end());
    hull.push_back(pivot);
    while(true)
    {
        //pivotHull에서 시작하는 벡터가 가장 왼쪽인 점 next를 찾는다.
        //평행인 점이 여러개 있으면 가장 먼 것을 선택한다.
        vector2 pivotHull=hull.back(), next=points[0];
        for(int i=1;i<n;++i)
        {
            double cross=ccw(pivotHull, next, points[i]);
            double dist=(next-pivotHull).norm()-(points[i]-pivotHull).norm();
            if(cross>0 || (cross==0 && dist<0))
                next=points[i];
        }
        //시작점으로 돌아왔으면 종료
        if(next==pivot) break;
        //next를 hull에 포함시킨다.
        hull.push_back(next);
    }
    return hull;
}
```

### 다각형 교차 판정 
1. 한 다각형이 다른 다각형에 포함되는 경우를 제외한다.  
2. 선분을 모두 확인하면서 서로 겹치거나 닿는 선분이 있으면 교차하는 것이다.  
```c++
//두 다각형이 서로 닿거나 겹치는지 여부를 반환한다.
bool polygonIntersects(const polygon& p, const polygon& q)
{
    int n=p.size(), m=q.size();
    //우선 한 다각형이 다른 다각형에 포함되어 있는 경우를 확인하자
    if(isInside(p[0],q) || isInside(q[0],p))
        return true;
    //이 외의 경우, 두 다각형이 서로 겹친다면 서로 닿는 두 변이 반드시 존재한다.
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            if(segmentIntersects(p[i],p[(i+1)%n],q[j],q[(j+1)%m]))
                return true;
    
    return false;
}
```
