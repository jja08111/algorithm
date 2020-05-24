#include <iostream>
#include <vector>
using namespace std;

struct RoadSign {
    int mStart, mEnd, mGap;
    void insert(int l, int m, int g) {
        mStart=l-m;
        mEnd=l;
        mGap=g;
    }
    int count(int here) {
        return (min(here,mEnd)-mStart)/mGap+1;
    }
};

int n, k;
vector<RoadSign> signs;

bool decision(int dist)
{
    int sum=0;
    for(int i=0;i<n;++i)
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
            tmp.insert(l,m,g);
            signs.push_back(tmp);
        }
        
        cout<<optimize()<<endl;
    }

    return 0;
}
