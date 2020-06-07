# 해결 
다각형의 교집합을 구하는 문제이다. 벡터를 이용하여 해결하면 구현하기 용이하다.  
이 문제의 핵심 아이디어는 직사각형이 볼록 다각형인 점을 이용하는 것이다.  
볼록 다각형이기 때문에 내부에 있는 점을 외적을 이용하여 쉽게 찾아낼 수 있다. 벡터의 진행방향의 왼쪽에 점이 있을 때 외적 값이 양수인 것을 이용하는 것이다.  

### 새로운 다각형 얻기 
다각형을 직사각형으로 자른 새로운 다각형을 얻기 위해서는 아래의 두 가지의 꼭지점을 구해야 한다.  
- 기존 다각형의 꼭지점 중 직선의 왼쪽에 있는 점들
- 직선이 기존 다각형을 가로지를 때, 변과 직선의 교차점들

위의 과정을 직사각형을 네 개의 직선으로 나눠서 구하면 된다.  
이 알고리즘은 [Sutherland-Hodgman algorithm](https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm)에 자세히 설명되어 있다.
```c++
//반평면과 단순 다각형의 교집합을 구한다.
//(a,b)를 포함하는 직선으로 다각형 p를 자른 뒤, (a,b)의 왼쪽에 있는 부분들을 반환한다. 
polygon cutPoly(const polygon& p, const vector2& a, const vector2& b)
{
    int n=p.size();
    //각 점이 반평면 내에 있는지 여부를 우선 확인한다.
    vector<bool> inside(n);
    for(int i=0;i<n;++i)
        inside[i]=ccw(a,b,p[i])>=0;
    
    polygon ret;
    //다각형의 각 변을 순회하면서 결과 다각형의 각 점을 발견한다.
    for(int i=0;i<n;++i)
    {
        int j=(i+1)%n;
        //반평면 내에 있는 점 p[i]는 항상 결과 다각형에 포함된다.
        if(inside[i])
            ret.push_back(p[i]);
        //변 p[i]-p[j]가 직선과 교차하면 교차점을 결과 다각형에 포함시킨다.
        if(inside[i]!=inside[j])
        {
            vector2 cross;
            lineIntersection(p[i],p[j],a,b,cross);
            ret.push_back(cross);
        }
    }
    return ret;
}

//서덜랜드-호지맨 알고리즘을 이용한 다각형 클리핑
polygon intersection(const polygon& p, double x1, double y1, double x2, double y2)
{
    vector2 a(x1,y1), b(x2,y1), c(x2,y2), d(x1,y2);
    polygon ret=cutPoly(p,a,b);
    ret=cutPoly(ret,b,c);
    ret=cutPoly(ret,c,d);
    ret=cutPoly(ret,d,a);
    return ret;
}
```
