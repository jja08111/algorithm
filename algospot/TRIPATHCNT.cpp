#include <iostream>
#include <cstring>
using namespace std;

int n,map[101][101];
int cache[101][101];
int countCache[101][101];

void init(void)
{
    cin>>n;
    
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<i+1;++j)
            scanf("%d",&map[i][j]);
        memset(cache[i],-1,sizeof(int)*(i+1));
        memset(countCache[i],-1,sizeof(int)*(i+1));
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

int count(int y, int x)
{
    if(y==n-1)
        return 1;
    
    int& ret=countCache[y][x];
    if(ret!=-1)
        return ret;
    
    ret=0;
    //세가지의 경우를 아래와 같이 코딩함으로써 훨씬 깔끔하고 간단해졌다.
    if(path(y+1,x)>=path(y+1,x+1)) ret+=count(y+1,x);
    if(path(y+1,x)<=path(y+1,x+1)) ret+=count(y+1,x+1);
    
    return ret;
}

int main(void)
{
    int testCase;
    
    cin>>testCase;
    
    while(testCase--)
    {
        init();
        
        cout<<count(0,0)<<endl;
    }
    
    return 0;
}
