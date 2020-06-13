#include <iostream>
#include <cstring>
using namespace std;

const int MAX=10000;

int n,wine[MAX];
int cache[MAX][3];

int solve(int here, int continues)
{
    if(continues==3)
        return -987654321;
    if(here==n)
        return 0;
    
    int& ret=cache[here][continues];
    if(ret!=-1)
        return ret;
    
    return ret=max(solve(here+1,0), solve(here+1,continues+1)+wine[here]);
}

int main()
{
    cin>>n;
    for(int i=0;i<n;++i)
        cin>>wine[i];
    memset(cache,-1,sizeof(cache));
    
    cout<<solve(0,0);
    
    return 0;
}
