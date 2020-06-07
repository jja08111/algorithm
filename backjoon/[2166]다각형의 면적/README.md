# 해결 
벡터의 외적을 이용하여 해결하였다.  
아주 간단히 설명하자면 다음과 같다.  
- 외적하고 2로 나눠주면 삼각형의 넓이를 구할 수 있는데, 외적시 방향에 따라 부호가 바뀐다.  
따라서 원점과 다각형의 모든 변을 외적한 값들의 합에서 2로 나눠주면 다각형의 면적을 구할 수 있다.  
```c++
struct vector2 {
    double x,y;
    explicit vector2(double x_=0, double y_=0) : x(x_), y(y_) {}
    
    double cross(const vector2& rhs) const {
        return x*rhs.y-y*rhs.x;
    }
};

typedef vector<vector2> polygon;

double area(const polygon& p)
{
    int n=p.size();
    double ret=0;
    for(int i=0;i<n;++i)
    {
        int j=(i+1)%n;
        ret+=p[i].cross(p[j]);
    }
    return fabs(ret)/2.0;
}
```
