#include <iostream>
#include <utility>
#include <cmath>
#include <algorithm>
using namespace std;

const int INF=987654321;
const double PI=2.0*acos(0);
int n;
double yPos[100], xPos[100], radius[100];
pair<double,double> ranges[100];

// ranges에 시작위치와 끝 위치를 중심각으로 변환하여 넣는다.
void convertToRange()
{
    for(int i=0;i<n;++i)
    {
        double location=fmod(2*PI+atan2(yPos[i],xPos[i]),2*PI);
        //초소의 중심, 감시범위와 성벽이 만나는곳, 성벽의 중심을 꼭짓점으로 하는
        //삼각형을 이용하여 각을 구한다.
        double range=2.0*asin(radius[i]/2.0/8.0);
        ranges[i]=make_pair(location-range,location+range);
    }
    sort(ranges,ranges+n);
}

int solveLinear(double begin, double end)
{
    int used=0, idx=0;
    while(begin<end)
    {
        //begin과 겹치는 구간 중 가장 늦게 끝나는 구간을 찾는다.
        double maxCover=-1;
        while(idx<n && ranges[idx].first<=begin)
        {
            maxCover=max(maxCover,ranges[idx].second);
            ++idx;
        }
        //덮을 구간을 찾지 못한 경우
        if(maxCover<=begin)
            return INF;
        begin=maxCover;
        ++used;
    }
    return used;
}

int solveCircular()
{
    int ret=INF;
    sort(ranges,ranges+n);
    for(int i=0;i<n;++i)
        if(ranges[i].first<=0 || ranges[i].second>=2*PI)
        {
            double begin=fmod(ranges[i].second, 2*PI);
            double end=fmod(ranges[i].first+2*PI, 2*PI);
            ret=min(ret, 1+solveLinear(begin, end));
        }
    return ret;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>n;
        for(int i=0;i<n;++i)
            cin>>yPos[i]>>xPos[i]>>radius[i];
        
        convertToRange();
        
        int ret=solveCircular();
        if(ret==INF)
            cout<<"IMPOSSIBLE"<<endl;
        else
            cout<<ret<<endl;
    }
    
    return 0;
}
