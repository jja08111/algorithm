#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n,k;
int c[1000],r[1000];

bool decision(double average)
{
    //sum(r[i]/c[i])<=x
    //sum(r[i])<=x*sum(c[i])
    //0<=sum(x*c[i]-r[i])
    //v[i]=x*c[i]-r[i]를 계산한다.
    vector<double> v;
    for(int i=0;i<n;++i)
        v.push_back(average*c[i]-r[i]);
    sort(v.begin(),v.end());
    
    //greedy
    double sum=0;
    for(int i=n-k;i<n;++i)
        sum+=v[i];
    return sum>=0;
}

double optimize()
{
    double lo=-1e-9, hi=1;
    for(int it=0;it<100;++it)
    {
        double mid=(lo+hi)/2.0;
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
        for(int i=0;i<n;++i)
            cin>>r[i]>>c[i];
        
        printf("%.10lf \n",optimize());
    }

    return 0;
}
