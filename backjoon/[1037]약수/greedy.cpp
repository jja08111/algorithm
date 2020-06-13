#include <iostream>
#include <algorithm>
using namespace std;

int solve(int n, int num[50])
{
    sort(num,num+n);
    
    return num[0]*num[n-1];
}

int main()
{
    int n,num[50];
    cin>>n;
    for(int i=0;i<n;++i)
        cin>>num[i];
    
    cout<<solve(n,num);

    return 0;
}
