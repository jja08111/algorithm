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

int n;
vector2 center[50];
int radius[50];

//2차 방정식 ax^2 + bx + c = 0 의 모든 실근을 크기 순서대로 반환한다.
vector<double> solve2(double a, double b, double c)
{
    double d=b*b - 4*a*c;
    //해가 없는 경우 
    if(d < -EPSILON)
        return vector<double>();
    //중근
    if(d < EPSILON)
        return vector<double>(1, -b/(2*a));
    
    vector<double> ret;
    ret.push_back((-b-sqrt(d))/(2*a));
    ret.push_back((-b+sqrt(d))/(2*a));
    return ret;
}

//here에 있던 공이 1초마다 dir만큼 굴러갈 때, center를 중심으로 하고
//반지름 radius인 장애물과 몇 초 후에 충돌하는지 반환한다.
//충돌하지 않을 경우 INFTY를 반환한다.
double hitCircle(vector2 here, vector2 dir, vector2 center, int radius)
{
    double a=dir.dot(dir);
    double b=2*dir.dot(here-center);
    double c=center.dot(center)+here.dot(here)-2*here.dot(center)-radius*radius;
    
    vector<double> sols=solve2(a,b,c);
    //충돌하지 않을 때
    if(sols.empty() || sols[0]<EPSILON)
        return INFTY;
    return sols[0];
}

//here에 있던 공이 dir 방향으로 굴러와 center를 중심으로 하는 장애물에서
//contact 위치에서 충돌했을 때 공의 새로운 방향을 반환한다.
vector2 reflect(vector2 dir, vector2 center, vector2 contact)
{
    return (dir-dir.project(contact-center)*2).normalize();
}

//공의 현재 위치와 방향이 주어질 때 최대 100번의 충돌을 출력한다.
void simulate(vector2 here, vector2 dir)
{
    dir=dir.normalize();
    int hitCount=0;
    while(hitCount<100)
    {
        //이번에 충돌할 장애물을 찾는다.
        int circle=-1;
        double time=INFTY*0.5;
        //각 장애물을 순회하며 가장 먼저 만나는 장애물을 찾는다.
        for(int i=0;i<n;++i)
        {
            double cand=hitCircle(here,dir,center[i],radius[i]+1);
            if(cand<time)
            {
                time=cand;
                circle=i;
            }
        }
        //더이상 장애물에 충돌하지 않고 게임판을 벗어난 경우
        if(circle==-1) break;
        
        //부딪히는 장애물의 번호를 출력한다.
        if(hitCount++) 
            cout<<" ";
        cout<<circle;
        //공의 새 위치를 계산한다.
        vector2 contact=here+dir*time;
        //부딪힌 위치와 새 방향으로 here과 dir을 변경한다.
        dir=reflect(dir,center[circle],contact);
        here=contact;
    }
    cout<<endl;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        vector2 here,dir;
        cin>>here.x>>here.y>>dir.x>>dir.y>>n;
        for(int i=0;i<n;++i)
            cin>>center[i].x>>center[i].y>>radius[i];
        
        simulate(here,dir);
    }
    return 0;
}
