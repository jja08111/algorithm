#include <iostream>
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
        return vector2(x-rhs.x,y-rhs.y);
    }
    
    double cross(const vector2& rhs) const {
        return x*rhs.y-y*rhs.x;
    }
};

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
    if(ab==0 && cd==0)
    {
        if(b<a) swap(a,b);
        if(d<c) swap(c,d);
        return !(b<c || d<a);
    }
    return ab<=0 && cd<=0;
}

int main()
{
    vector2 a,b,c,d;
    cin>>a.x>>a.y>>b.x>>b.y;
    cin>>c.x>>c.y>>d.x>>d.y;
    
    if(isCrossed(a,b,c,d))
        cout<<1;
    else
        cout<<0;

    return 0;
}
