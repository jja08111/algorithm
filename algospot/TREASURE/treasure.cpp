#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double EPSILON=1e-9;
const double INFTY=1e200;
const double PI=2.0*acos(0.0);

//2차원 벡터를 표현한다. 
struct vector2 {
    double x, y;
    
    explicit vector2(double x_=0, double y_=0) : x(x_), y(y_) {}
    
    //두 벡터의 비교
    bool operator == (const vector2& rhs) const {
        return x==rhs.x && y==rhs.y;
    }
    bool operator < (const vector2& rhs) const {
        return x!=rhs.x ? x<rhs.x : y<rhs.y;
    }
    
    //벡터의 덧셈과 뺄셈
    vector2 operator + (const vector2& rhs) const {
        return vector2(x+rhs.x, y+rhs.y);
    }
    vector2 operator - (const vector2& rhs) const {
        return vector2(x-rhs.x, y-rhs.y);
    }
    
    //실수로 곱셈
    vector2 operator * (double rhs) const {
        return vector2(x*rhs, y*rhs);
    }
    
    //벡터의 길이를 반환
    double norm() const { return hypot(x,y); }
    
    //방향이 같은 단위 벡터(unit vector)를 반환한다.
    //영벡터에 대해 호출한 경우 반환 값은 정의되지 않는다.
    vector2 normalize() const {
        return vector2(x/norm(), y/norm());
    }
    
    //x축의 양의 방향으로부터 이 벡터까지 반시계 방향으로 잰 각도
    double polar() const {
        return fmod(atan2(y,x)+2*PI, 2*PI);
    }
    
    //벡터의 내적과 외적 구현
    double dot(const vector2& rhs) const {
        return x*rhs.x + y*rhs.y;
    }
    double cross(const vector2& rhs) const {
        return x*rhs.y - rhs.x*y;
    }
    
    //이 벡터를 rhs에 사영한 결과
    vector2 project(const vector2& rhs) const {
        vector2 r=rhs.normalize();
        return r*r.dot(*this); 
    }
};

typedef vector<vector2> polygon;

double ccw(vector2 p, vector2 a, vector2 b)
{
    return (a-p).cross(b-p);
}

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

//주어진 단순 다각형 p의 넓이를 구한다.
//p는 각 꼭지점의 위치 벡터의 집합으로 주어진다. 
double area(const polygon& p)
{
    double ret=0;
    for(int i=0;i<p.size();++i)
    {
        int j=(i+1)%p.size();
        ret+=p[i].x*p[j].y-p[j].x*p[i].y;
    }
    return fabs(ret)/2.0;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        double x1,y1,x2,y2;
        int n;
        polygon p;
        
        cin>>x1>>y1>>x2>>y2>>n;
        for(int i=0;i<n;++i)
        {
            vector2 tmp;
            cin>>tmp.x>>tmp.y;
            p.push_back(tmp);
        }
   
        double ret=area(intersection(p,x1,y1,x2,y2));
        printf("%.10lf \n",ret);
    }
    return 0;
}
