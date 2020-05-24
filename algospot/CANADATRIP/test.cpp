#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct RoadSign {
    int mStart, mEnd, mGap;
    void insert(int l, int m, int g) {
        mStart=l-m;
        mEnd=l;
        mGap=g;
    }
};

int n, k;
vector<RoadSign> sings;

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>n>>k;
        sings.clear();
        for(int i=0;i<n;++i)
        {
            RoadSign tmp;
            int l,m,g;
            scanf("%d %d %d",&l,&m,&g);
            tmp.insert(l,m,g);
            sings.push_back(tmp);
        }
    }

    return 0;
}
