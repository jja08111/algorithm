# 해결 
두 벡터의 외적을 이용하여 이 문제를 간단하게 해결할 수 있다.  
A,B 두 선분이 교차하는 경우 
- A 선분
- B 선분의 한 끝점과 A 선분의 기준 끝점을 잇는 선분

위 두 선분을 외적한 값이 하나는 양수 하나는 음수가 나온다.  
이러한 성질을 이용할 것이기 때문에 벡터를 구현했다.  
```c++
struct vector2 {
    double x,y;
    explicit vector2(double x_=0, double y_=0) : x(x_), y(y_) {}
    bool operator == (const vector2& rhs) const {
        return x==rhs.x && y==rhs.y;
    }
    bool operator < (const vector2& rhs) const {
        return x!=rhs.x ? x<rhs.x : y<rhs.y;
    }
    
    vector2 operator - (const vector2& rhs) const {
        return vector2(x-rhs.x,y-rhs.y);
    }
    //벡터의 외적한 값을 실수로 반환한다.  
    double cross(const vector2& rhs) const {
        return x*rhs.y-y*rhs.x;
    }
};
```

여기서 주의할 점은 평행한 두 선분에 대한 처리이다.  
이는 평행한 선분이 겹치거나 닿을 때에 겹치는 것으로 간주하여 코드를 작성하여 해결할 수 있다.
```c++
double ccw(vector2 a, vector2 b)
{
    return a.cross(b);
}

double ccw(vector2 p, vector2 a, vector2 b)
{
    return ccw(a-p,b-p);
}

bool isCrossed(vector2 a, vector2 b, vector2 c, vector2 d)
{
    double ab=ccw(a,b,c)*ccw(a,b,d);
    double cd=ccw(c,d,a)*ccw(c,d,b);
    //두 선분이 평행할 경우
    if(ab==0 && cd==0)
    {
        if(b<a) swap(a,b);
        if(d<c) swap(c,d);
        return !(b<c || d<a);
    }
    return ab<=0 && cd<=0;
}
```

# 회고 
두 선분이 평행할 때의 조건문을 잘못 설정하여 오류가 발생했다.  
이는 세 점이 한 직선에 있을 경우를 처리하는 방법으로 해결 할 수 있을 것이라고 잘못생각했기 때문이다.  
```c++
bool isCrossed(vector2 a, vector2 b, vector2 c, vector2 d)
{
    double ab=ccw(a,b,c)*ccw(a,b,d);
    double cd=ccw(c,d,a)*ccw(c,d,b);
    if(ab==0 && cd==0)
    //if(ab==0 || cd==0)  <--------------------------
    {
        if(b<a) swap(a,b);
        if(d<c) swap(c,d);
        return !(b<c || d<a);
    }
    return ab<=0 && cd<=0;
}
```

# 참고 
알고리즘 문제 해결 전략, 구종만, 인사이트 
