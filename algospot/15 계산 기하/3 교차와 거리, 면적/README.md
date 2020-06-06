# 교차와 거리, 면적 
## 직선과 직선의 교차 
직선을 한 점과 방향 벡터로 표현한다.  
- a + p x b  

(https://www.mathfactory.net/11884 에서 직선의 방정식에 관한 내용을 자세히 볼 수 있다.)   
a + p x b 와 c + q x d 의 교점을 구하기 위해서 방정식 a + p x b = c + q x d 을 풀면 된다.  
이 식을 좌표에 대해 나타내면 다음과 같은 연립 방정식을 얻을 수 있다.  
- ax + p x bx = cx + q x dx
- ay + p x by = cy + q x dy

위 식을 p에 대해 풀어 외적으로 간략화 하면 다음과 같다.  
- p = {(c - a) X d} / (b X d)

따라서 결과적으로 구한 p를 a + p x b에 대입해 원하는 점을 구할 수 있다.  
```c++
//(a,b)를 포함하는 선과 (c,d)를 포함하는 선의 교점을 x에 반환한다. 
//두 선이 평행이면 (겹치는 경우를 포함) 거짓을, 아니면 참을 반환한다.
bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x)
{
    double det=(b-a).cross(d-c);
    //두 선이 평행한 경우 
    if(fabs(det)<EPSILON) return false;
    //b와 d는 각 직선과 평행한 방향 벡터이니 b-a, d-c로 표현하고 있다.  
    x=a+(b-a)*((c-a).cross(d-c)/det);
    return true;
}
```
## 선분과 선분의 교차 
두 직선의 교차점을 확인하고 교차점이 두 선분의 위에 오는지 확인하여 교차점을 찾을 수 있다.  
하지만 한 직선 위에 있는 두 선분의 경우를 유의해야 한다. 이 두선분의 관계는 아래의 네 가지중 하나이다.  
1. 두 선분이 겹치지 않음  
2. 두 선분이 한점에서 닿음  
3. 두 선분이 겹쳐짐  
4. 한 선분이 다른 선분 안에 포함됨  

1번을 제외하고는 두 선분이 교차한다고 할 수 있다. 이와 같은 구현을 아래의 코드에서 볼 수 있다.  
```c++
//(a,b)와 (c,d)가 평행한 두 선분일 때 이들이 한 점에서 겹치는지 확인한다. 
bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p)
{
    if(b<a) swap(a,b);
    if(d<c) swap(c,d);
    //한 직선이 위에 없거나 두 선분이 겹치지 않는 경우를 우선 걸러낸다. 
    if(ccw(a,b,c)!=0 || b<c || d<a) 
        return false;
    //두 선분은 확실히 겹친다. 교차점을 하나 찾자.
    if(a<c) 
        p=c;
    else
        p=a;
    return true;
}

//p가 선분(a,b)를 감싸면서 각 변이 x,y축에 평행한 최소 사각형 내부에 있는지 확인한다. 
//a,b,p는 일직선 상에 있다고 가정한다. 
bool inBoundingRectangle(vector2 p, vector2 a, vector2 b) {
    if(b<a) swap(a,b);
    return p==a || p==b || (a<p && p<b);
}

//(a,b)선분과 (c,d)선분의 교점을 p에 반환한다.
//교점이 여러 개일 경우 아무 점이나 반환한다. 
//두 선분이 교차하지 않을 경우 false를 반환한다. 
bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p)
{
    //두 직선이 평행인 경우를 우선 예외로 처리한다.
    if(!lineIntersection(a,b,c,d,p))
        return parallelSegments(a,b,c,d,p);
    //p가 두 선분에 포함되어 있는 경우에만 참을 반환한다.
    return inBoundingRectangle(p,a,b) && inBoundingRectangle(p,c,d);
}
```

## 선분과 선분의 교차: 교차점이 필요 없을 때
ccw()를 이용하여 교차점을 구하지 않고 교차점의 여부를 쉽게 판단할 수 있다.  
두 선분이 교차하려면 ccw(a,b,c)와 ccw(a,b,d) 중 하나는 양수, 하나는 음수여야 선분(a,b)에 대해 c와 d가 좌,우측으로 위치해 있다.   
마찬가지로 ccw(a,b,c)와 ccw(a,b,d)의 곱 또한 음수여야 한다.   

예외로는 두 선분이 한 직선위에 있을 경우를 처리해야 한다.  
```c++
//두 선분이 서로 접촉하는지 여부를 판단한다.
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d)
{
    double ab=ccw(a,b,c)*ccw(a,b,d);
    double cd=ccw(c,d,a)*ccw(c,d,b);
    //두 선분이 한 직선위에 있거나 끝점이 겹치는 경우
    if(ab==0 && cd==0)
    {
        if(b<a) swap(a,b);
        if(d<c) swap(c,d);
        return !(b<c || d<a);
    }
    return ab<=0 && cd<=0;
}
```

## 점과 선 사이의 거리 
점 p가 선 (a,b)에 내리는 수선의 발을 계산한 뒤 p와의 거리를 구하면 된다.  
벡터의 내적을 이용하면 수선의 발을 쉽게 구할 수 있다.  
```c++
//점 p에서 (a,b)직선에 내린 수선의 발을 구한다.
vector2 perpendicularFoot(vector2 p, vector2 a, vector2 b) {
    return a+(p-a).project(b-a);
}

//점 p와 (a,b)직선 사이의 거리를 구한다. 
double pointToLine(vector2 p, vector2 a, vector2 b) {
    return (p-perpendicularFoot(p,a,b)).norm();
}
```
이는 선분과 선분 사이의 거리를 구하는 데 유용하게 쓰인다.
