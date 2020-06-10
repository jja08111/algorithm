#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

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
        return vector2(x-rhs.x, y-rhs.y);
    }
    
    double norm() const { return hypot(x,y); }
    
    double cross(const vector2& rhs) const {
        return x*rhs.y-y*rhs.x;
    }
};

typedef vector<vector2> polygon;

double ccw(vector2 p, vector2 a, vector2 b)
{
    return (a-p).cross(b-p);
}

bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d)
{
    double ab=ccw(a,b,c)*ccw(a,b,d);
    double cd=ccw(c,d,a)*ccw(c,d,b);
    
    if(ab==0 && cd==0)
    {
        //각 직선을 a가 왼쪽, c가 왼쪽에 위치하도록 한다.
        if(b<a) swap(a,b);
        if(d<c) swap(c,d);
        return !(b<c || d<a);
    }
    return ab<=0 && cd<=0;
}

bool isInside(vector2 q, const polygon& p)
{
    int crosses=0;
    for(int i=0;i<p.size();++i)
    {
        int j=(i+1)%p.size();
        if((p[i].y>q.y) != (p[j].y>q.y))
        {
            //double atX=(q.y-p[i].y)*(p[j].x-p[i].x)/(p[j].y-p[i].y)+p[i].x;
            double atX=(q.y-p[i].y)*(p[i].x-p[j].x)/(p[i].y-p[j].y)+p[i].x;
            if(q.x<atX)
                ++crosses;
        }
    }
    return crosses%2 > 0;
}

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

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        polygon p, q;
        int n;
        cin>>n;
        for(int i=0;i<n;++i)
        {
            vector2 tmp;
            bool isNerd;
            cin>>isNerd>>tmp.x>>tmp.y;
            if(isNerd)
                p.push_back(tmp);
            else
                q.push_back(tmp);
        }
        p=giftWrap(p);
        q=giftWrap(q);
        
        if(polygonIntersects(p,q))
            cout<<"THEORY IS INVALID"<<endl;
        else
            cout<<"THEORY HOLDS"<<endl;
    }
    return 0;
}
