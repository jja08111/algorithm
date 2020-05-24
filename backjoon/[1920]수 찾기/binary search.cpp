#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n,m;
int num[100001];

bool findNum(int a)
{
    int lo=0, hi=n-1;
    for(int it=0;it<20;++it)
    {
        int mid=(lo+hi)/2;
        
        if(num[hi]==a)
            return true;
        
        if(num[mid]>=a)
            hi=mid;
        else 
            lo=mid;
    }
    return false;
}

int main()
{
    cin>>n;
    for(int i=0;i<n;++i)
    {
        int tmp;
        scanf("%d",&num[i]);
    }
    sort(num,num+n);
    
    cin>>m;
    for(int i=0;i<m;++i)
    {
        int tmp;
        scanf("%d",&tmp);
        if(findNum(tmp))
            printf("1 \n");
        else
            printf("0 \n");
    }
    
    return 0;
}
