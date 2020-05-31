#include <iostream>
using namespace std;

int getRatio(long long total, long long win)
{
    return (win*100)/total;
}

int neededGames(long long total, long long win)
{
    long long ratio=getRatio(total,win)+1;
    
    if(ratio>=100)
        return -1;
    
    double ret=(double)(ratio*total-100*win)/(100-ratio);
    int temp=(int)ret;
    
    if(ret-(double)temp>0.0)
        return ret+1;
    return ret;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int total,win;
        cin>>total>>win;
        
        cout<<neededGames(total,win)<<endl;
    }
    return 0;
}
