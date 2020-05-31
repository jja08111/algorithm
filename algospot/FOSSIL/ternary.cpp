#include <iostream>
#include <vector>
#include <utility>
using namespace std;

struct point {
    double x,y;
};

// 입력에 주어진 볼록 다각형 
vector<point> hull1, hull2;
// 위 껍질에 속하는 선분들과 아래 껍길에 속하는 선분들
vector<pair<point,point> > upper, lower;

// 위 껍질과 아래 껍질을 분해
void decompose(const vector<point>& hull)
{
    int n=hull.size();
    for(int i=0;i<n;++i)
    {
        if(hull[i].x<hull[(i+1)%n].x)
            lower.push_back(make_pair(hull[i],hull[(i+1)%n]));
        else if(hull[i].x>hull[(i+1)%n].x)
            upper.push_back(make_pair(hull[i],hull[(i+1)%n]));
    }
}

// [a.x, b.x] 구간 안에 x가 포함되나 확인
bool between(const point& a, const point& b, double x)
{
    return (a.x<=x && x<=b.x) || (b.x<= x && x<=a.x);
}

// (a,b) 선분과 주어진 위치의 수직선이 교차하는 위치의 y값 반환
double at(const point& a, const point& b, double x)
{
    double dy=b.y-a.y, dx=b.x-a.x;
    // 삼각형 비례식 이용
    return a.y+dy*(x-a.x)/dx;
}

// 두 다각형의 교집합을 x위치의 수직선으로 잘랐을 때 단면의 길이를 반환
double vertical(double x)
{
    double minUp=1e20, maxLow=-1e20;
    // 위 껍질의 선분을 순회 하며 최소 y좌표를 찾는다.
    for(int i=0;i<upper.size();++i)
        if(between(upper[i].first, upper[i].second, x))
            minUp=min(minUp,at(upper[i].first, upper[i].second, x));
    // 아래 껍질의 선분을 순회 하며 최소 y좌표를 찾는다.
    for(int i=0;i<lower.size();++i)
        if(between(lower[i].first, lower[i].second, x))
            maxLow=max(maxLow,at(lower[i].first, lower[i].second, x));
    return minUp-maxLow;
}

double minX(vector<point>& a)
{
    double ret=a[0].x;
    for(int i=1;i<a.size();++i)
        ret=min(ret,a[i].x);
    return ret;
}

double maxX(vector<point>& a)
{
    double ret=a[0].x;
    for(int i=1;i<a.size();++i)
        ret=max(ret,a[i].x);
    return ret;
}

double solve()
{
    // 수직선이 두 다각형을 모두 만나는 x 좌표의 범위를 구한다.
    double lo=max(minX(hull1),minX(hull2));
    double hi=min(maxX(hull1),maxX(hull2));
    
    // 예외: 두 다각형이 좌우로 배치되어 아예 겹치지 않을 경우
    if(hi<lo)
        return 0;
    
    for(int iter=0;iter<100;++iter)
    {
        double aab=(lo*2+hi)/3.0;
        double abb=(lo+2*hi)/3.0;
        if(vertical(aab)<vertical(abb))
            lo=aab;
        else
            hi=abb;
    }
    // 두 다각형이 겹치지 않게 상하로 배치되면 0.0 을 반환
    return max(0.0,vertical(hi));
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int n,m;
        cin>>n>>m;
        
        hull1.clear();
        hull2.clear();
        for(int i=0;i<n;++i)
        {
            point temp;
            cin>>temp.x>>temp.y;
            hull1.push_back(temp);
        }
        for(int i=0;i<m;++i)
        {
            point temp;
            cin>>temp.x>>temp.y;
            hull2.push_back(temp);
        }
        
        lower.clear();
        upper.clear();
        decompose(hull1);
        decompose(hull2);
        
        printf("%.10lf \n",solve());
    }
    return 0;
}
