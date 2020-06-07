#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

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
