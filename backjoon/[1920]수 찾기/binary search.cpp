#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n,m;
int num[100001];

bool findNum(int a)
{
    int lo=0, hi=n-1;
    while(hi>=lo)
    {
        int mid=(lo+hi)/2;
        
        if(num[mid]==a)
            return true;
        
        if(num[mid]>a)
            hi=mid-1;
        else 
            lo=mid+1;
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
