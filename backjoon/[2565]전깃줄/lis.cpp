#include <iostream>
#include <utility>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
int cache[101];
vector<pair<int,int> > line;

void init(void)
{
    cin>>n;
    for(int i=0;i<n;++i)
    {
        int a,b;
        cin>>a>>b;
        line.push_back(make_pair(a,b));
    }
    sort(line.begin(),line.end());
    memset(cache,-1,sizeof(cache));
}

int lis(int start)
{
    int& ret=cache[start+1];
    if(ret!=-1)
        return ret;
    
    ret=1;
    for(int next=start+1;next<n;++next)
        if(start==-1 || line[start].second<line[next].second)
            ret=max(ret,lis(next)+1);
    
    return ret;
}

int main(void)
{
    init();
    
    int ret=n-(lis(-1)-1);
    
    cout<<ret;
    
    return 0;
}
