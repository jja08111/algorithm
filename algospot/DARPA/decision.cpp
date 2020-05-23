#include <iostream>
#include <vector>
using namespace std;

//결정 문제: 정렬되어 있는 locations중 cameras를 선택해 모든 카메라 간의 간격이
//gap이상이 되는 방법이 있는지를 반환한다.
bool decision(const vector<double>& location, int cameras, double gap)
{
    double limit=-1;
    int installed=0;
    for(int i=0;i<location.size();++i)
        if(limit<=location[i])
        {
            ++installed;
            //location에서 gap만큼 떨어져야 카메라를 설치할 수 있다.
            limit=location[i]+gap;
        }
    //cameras대 이상을 설치할 수 있으면 성공
    return installed>=cameras;
}

double optimize(const vector<double>& location, int cameras)
{
    double lo=0, hi=241;
    //반복문 불변식: decision(lo) && !decision(hi)
    for(int it=0;it<100;++it)
    {
        double mid=(lo+hi)/2.0;
        //mid만큼 간격을 벌려도 설치 가능하면 답은 [mid,hi]에 있다.
        if(decision(location,cameras,mid))
            lo=mid;
        else
            hi=mid;
    }
    return lo;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int cameraNum, locationNum;
        vector<double> location;
        
        cin>>cameraNum>>locationNum;
        for(int i=0;i<locationNum;++i)
        {
            double tmp; cin>>tmp;
            location.push_back(tmp);
        }
        
        printf("%.2lf \n",optimize(location,cameraNum));
    }

    return 0;
}
