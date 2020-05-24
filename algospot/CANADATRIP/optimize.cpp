#include <iostream>
#include <vector>
using namespace std;

struct RoadSign {
    int mStart, mEnd, mGap;
    void init(int l, int m, int g) {
        mStart=l-m;
        mEnd=l;
        mGap=g;
    }
    int count(int here) {
        //구간 [start, min(here,end)]에서 표지판의 개수 반환
        return (min(here,mEnd)-mStart)/mGap+1;
    }
};

int n, k;
vector<RoadSign> signs;

//dist 지점까지 가면서 표지판이 k개 이상인가?
bool decision(int dist)
{
    int sum=0;
    for(int i=0;i<n;++i)
        //표지판이 하나라도 존재할때
        if(dist>=signs[i].mStart)
        {
            sum+=signs[i].count(dist);
            if(sum>=k)
                return true;
        }
    return false;
}

int optimize()
{
    int lo=-1, hi=8030001;
    for(int it=0;it<100;++it)
    {
        int mid=(lo+hi)/2;
        if(decision(mid))
            hi=mid;
        else
            lo=mid;
    }
    return hi;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>n>>k;
        signs.clear();
        for(int i=0;i<n;++i)
        {
            RoadSign tmp;
            int l,m,g;
            
            scanf("%d %d %d",&l,&m,&g);
            tmp.init(l,m,g);
            signs.push_back(tmp);
        }
        
        cout<<optimize()<<endl;
    }

    return 0;
}
