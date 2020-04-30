#include <iostream>
#include <cstring>
using namespace std;

const int INF=987654321;
int cache[1000001]={0,};

//재귀함수(top-down)이 아닌 반복문(bottom-up)방식 
int solve(int n)
{
    cache[1]=0;
    
    for(int i=2;i<=n;++i)
    {
        cache[i]=cache[i-1]+1;
        if(i%2==0)
            cache[i]=min(cache[i],cache[i/2]+1);
        if(i%3==0)
            cache[i]=min(cache[i],cache[i/3]+1);
    }
    
    return cache[n];
}

int main(void)
{
    int n; cin>>n;

    cout<<solve(n);
    
    return 0;
}
