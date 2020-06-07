# 해결 
이 문제는 벡터의 외적을 이용하는 문제이다.  
원점을 기준으로 벡터 p 왼쪽 180내에 벡터 q가 있을 때 pXq를 구하면 양수가 나오고 그 반대의 경우 음수가 나온다.  
이러한 부분을 이용하여 벡터를 구현하고 1번 지점에서 2번 지점으로 가는 벡터와 1번 지점에서 3번 지점으로 가는 벡터를 외적하여 답을 구했다.  
```c++
struct vector2 {
    double x,y;
    explicit vector2(double x_=0, double y_=0) : x(x_), y(y_) {}
    vector2 operator - (const vector2& rhs) const {
        return vector2(x-rhs.x, y-rhs.y);
    }
    double cross(const vector2& rhs) const {
        return x*rhs.y-y*rhs.x;
    }
};

double ccw(vector2 p, vector2 a, vector2 b)
{
    return (a-p).cross(b-p);
}

int main()
{
    vector2 p[3];
    for(int i=0;i<3;++i)
        cin>>p[i].x>>p[i].y;
    
    double ret=ccw(p[0],p[1],p[2]);
    if(ret>0)
        cout<<1;
    else if(ret==0)
        cout<<0;
    else
        cout<<-1;
    
    return 0;
}
```
