#include <iostream>
using namespace std;

int n,k;
int cost[100],cache[100001];

void init(void)
{
    cin>>n>>k;
    for(int i=0;i<n;++i)
        cin>>cost[i];
}

int main(void)
{
    init();
    
    cache[0]=1;
    
    for (int c = 0; c < n; c++) 
        for (int w = 1; w <= k; w++)
            if (w - cost[c] >= 0)
                cache[w] += cache[w - cost[c]];

    cout<<cache[k]<<endl;
}
