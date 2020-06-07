#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

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

int main()
{
    int n;
    cin>>n;
    
    polygon p(n);
    for(int i=0;i<n;++i)
        cin>>p[i].x>>p[i].y;
    
    printf("%.1lf",area(p));
    
    return 0;
}
