#include <iostream>
using namespace std;

int map[100][100];
int cache[100][100];
int n;

void init(void)
{
    cin>>n;
    
    for(int y=0;y<n;++y)
        for(int x=0;x<y+1;++x)
            cin>>map[y][x];
}

int iterative(void)
{
    //기저사례를 계산한다.
    for(int i=0;i<n;++i)
        cache[n-1][i]=map[n-1][i];
    
    //나머지를 계산한다.
    for(int y=n-2;y>=0;--y)
        for(int x=0;x<y+1;++x)
            cache[y][x]=max(cache[y+1][x],cache[y+1][x+1])+map[y][x];

    return cache[0][0];
}

int main(void)
{
    int testCase;
    
    cin>>testCase;
    
    while(testCase--)
    {
        init();
        
        cout<<iterative()<<endl;
    }

    return 0;
}
