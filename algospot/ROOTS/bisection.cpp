#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

// 단일 변수 다항식 p의 계수가 주어질 떄 미분한 결과 p'의 계수를 반환
vector<double> differentiate(const vector<double>& poly)
{
    int n=poly.size()-1;
    vector<double> ret;
    for(int i=1;i<=n;++i)
        ret.push_back(i*poly[i]);
    return ret;
}

// 1차 혹은 2차 방적식을 푼다.
vector<double> solveNavie(const vector<double>& poly)
{
    int n=poly.size()-1;
    vector<double> ret;
    switch(n)
    {
    case 1:
        ret.push_back(-poly[0]/poly[1]);
        break;
    case 2:
        double a=poly[2], b=poly[1], c=poly[0];
        ret.push_back((-b+sqrt(pow(b,2)-4*a*c))/(2*a));
        ret.push_back((-b-sqrt(pow(b,2)-4*a*c))/(2*a));
        break;
    }
    sort(ret.begin(),ret.end());
    return ret;
}

// 다항식 f(x)의 계수 poly가 주어질 떄, f(x0)를 반환
double evaluate(const vector<double>& poly, double x0)
{
    int n=poly.size()-1;
    double ret=0;
    for(int i=0;i<=n;++i)
        ret+=pow(x0,i)*poly[i];
    return ret;
}

const double LIMIT=10;
// 방정식 sum(poly[i]*x^i)=0의 근을 반환
vector<double> solve(const vector<double>& poly)
{
    int n=poly.size()-1;
    
    // 기저사례: 2차 이하의 방정식들은 풀 수 있다.
    if(n<=2)
        return solveNavie(poly);
    
    // 방정식을 미분해서 n-1차 방정식을 얻는다.
    vector<double> derivative=differentiate(poly);
    vector<double> sols=solve(derivative);
    
    // 이 극점들 사이를 하나하나 검사하며 근이 있나 확인한다.
    sols.insert(sols.begin(), -LIMIT-1);
    sols.insert(sols.end(), LIMIT+1);
    vector<double> ret;
    for(int i=0;i+1<sols.size();++i)
    {
        double x1=sols[i], x2=sols[i+1];
        double y1=evaluate(poly,x1), y2=evaluate(poly,x2);
        // f(x1)과 f(x2)의 부호가 같은 경우 답은 없다.
        if(y1*y2>0)
            continue;
        // 불변 조건: f(x1)<=0<(fx2)
        if(y1>y2)
        {
            swap(y1,y2);
            swap(x1,x2);
        }
        // 이분법 이용
        for(int iter=0;iter<100;++iter)
        {
            double mx=(x1+x2)/2;
            double my=evaluate(poly,mx);
            if(y1*my>0)
            {
                y1=my;
                x1=mx;
            }
            else
            {
                y2=my;
                x2=mx;
            }
        }
        ret.push_back((x1+x2)/2);
    }
    sort(ret.begin(),ret.end());
    return ret;
}

int main(void)
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int n;
        cin>>n;
        vector<double> poly(n+1);
        for(int i=n;i>=0;--i)
            cin>>poly[i];
        
        vector<double> ret=solve(poly);
        for(int i=0;i<n;++i)
            printf("%.10lf ",ret[i]);
        cout<<endl;
    }
    return 0;
}
