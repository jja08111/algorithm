#include <iostream>
using namespace std;

const int MAX_N=2000000000;

int winRatio(long long total, long long win)
{
    return win*100/total;
}

int neededGames(long long total, long long win)
{
    if(winRatio(total,win)==winRatio(total+MAX_N,win+MAX_N))
        return -1;
    
    long long lo=0, hi=MAX_N;
    int current=winRatio(total,win);
    while(lo+1<hi)
    {
        long long mid=(lo+hi)/2;
        int next=winRatio(total+mid,win+mid);
        if(next > current)
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
        long long total,win;
        cin>>total>>win;
        
        cout<<neededGames(total,win)<<endl;
    }
    return 0;
}
