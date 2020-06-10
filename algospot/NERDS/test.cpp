#include <iostream>
#include <vector>
#include <cmath>

struct vector2 {
    double x,y;
    explicit vector2(double x_=0, double y_=0) : x(x_), y(y_) {}
    
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
}

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
        if(b<a) swap(a,b);
        if(d<c) swap(c,d);
        return !(b<c || d<a);
    }
    return ab<=0 && cd<=0;
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

int main()
{
    

    return 0;
}
