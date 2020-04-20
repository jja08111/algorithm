#include <iostream>
#include <cstring>
using namespace std;

int map[101][101];
int cache[101][101];
int n;

void init(void)
{
    cin>>n;
    
    for(int y=0;y<n;++y)
        for(int x=0;x<y+1;++x)
        {
            cin>>map[y][x];
            cache[y][x]=-1;
        }
}

int path(int y, int x)
{
    if(y==n-1)
        return map[y][x];
    
    int& ret=cache[y][x];
    if(ret!=-1)
        return ret;
    
    return ret=map[y][x]+max(path(y+1,x),path(y+1,x+1));
}

int main(void)
{
    int testCase;
    
    cin>>testCase;
    
    while(testCase--)
    {
        init();
        
        cout<<path(0,0)<<endl;
    }

    return 0;
}
