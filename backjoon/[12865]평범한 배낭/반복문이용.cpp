#include <iostream>

using namespace std;

int main(void)
{
    int n,limit,weight[100],value[100];
    // index : 남은 무게, value : 가치의 합
    int cache[100001]={0,};
    
    cin>>n>>limit;
    for(int i=0;i<n;++i)
    {
        cin>>weight[i]>>value[i];
        for(int j=limit;j>=weight[i];--j)
            cache[j]=max(cache[j],cache[j-weight[i]]+value[i]);
    }
    
    cout<<cache[limit];
    
    return 0;
}
