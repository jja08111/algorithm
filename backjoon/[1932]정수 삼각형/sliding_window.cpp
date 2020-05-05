#include <iostream>
using namespace std;

int n,map[500][500];
int cache[2][500];

void init(void)
{
    cin>>n;
    
    for(int i=0;i<n;++i)
        for(int j=0;j<i+1;++j)
            cin>>map[i][j];
}

int getMaxSum(void)
{
    //기저사례
    for(int x=0;x<n;++x)
        cache[(n-1)%2][x]=map[n-1][x];
    
    for(int y=n-2;y>=0;--y)
        for(int x=0;x<y+1;++x)
            cache[y%2][x]=max(cache[(y+1)%2][x],cache[(y+1)%2][x+1])+map[y][x];
    
    return cache[0][0];
}

int main(void)
{
    init();
    
    cout<<getMaxSum();
    
    return 0;
}
