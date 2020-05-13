#include <iostream>
using namespace std;

int n,coins[10];

int getMinCoinsNum(int remain)
{
    int needs=0;
    
    for(int i=n-1;i>=0;--i)
        while(remain-coins[i]>=0)
        {
            remain-=coins[i];
            ++needs;
        }
    
    return needs;
}

int main(void)
{
    int k;
    cin>>n>>k;
    
    for(int i=0;i<n;++i)
        cin>>coins[i];
    
    cout<<getMinCoinsNum(k);
    
    return 0;
}
