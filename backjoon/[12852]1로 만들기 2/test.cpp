/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <cstring>
using namespace std;

const int INF=987654321, MAX=1000001;

int cache[MAX], previous[MAX];

int solve(int n)
{
    if(n==1)
        return 0;
    
    int& ret=cache[n];
    if(ret!=-1)
        return ret;
    
    ret=INF;
    if(n%3==0)
    {
        ret=1+solve(n/3);
        previous[n]=n/3;
    }
    if(n%2==0)
    {
        int cand=1+solve(n/2);
        if(cand<ret)
        {
            ret=cand;
            previous[n]=n/2;
        }
    }
    int cand=1+solve(n-1);
    if(cand<ret)
    {
        ret=cand;
        previous[n]=n-1;
    }
    return ret;
}

int main()
{
    int n;
    cin>>n;
    
    memset(cache,-1,sizeof(cache));
    cout<<solve(n)<<endl;
    
    int idx=n;
    while(true)
    {
        cout<<idx<<endl;
        if(idx==1)
            break;
        idx=previous[idx];
    }

    return 0;
}
