#include <iostream>
#include <cstring>
using namespace std;

const int MAX=100000;
int n,seq[MAX],psum[MAX+1];
int cache[MAX];

void preCacl()
{
    psum[0]=0;
    psum[1]=seq[0];
    for(int i=2;i<=n;++i)
        psum[i]=psum[i-1]+seq[i-1];
}

int solve(int start)
{
    if(start>n)
        return 0;
    
    int& ret=cache[start];
    if(ret!=-1)
        return ret;
    
    ret=psum[start]-psum[start-1];
    
    ret=max(ret,solve(start+1));
    
    for(int end=start;end<n;++end)
        ret=max(ret,psum[end]-psum[start-1]);
    
    return ret;
}

int main()
{
    cin>>n;
    for(int i=0;i<n;++i)
        cin>>seq[i];
    
    preCacl();
    memset(cache,-1,sizeof(cache));
    
    cout<<solve(1);
    return 0;
}
