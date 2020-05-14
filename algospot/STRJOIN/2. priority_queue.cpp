#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n;

int getMinSum(const vector<int>& lengths)
{
    priority_queue<int,vector<int>,greater<int> > pq;
    for(int i=0;i<n;++i)
        pq.push(lengths[i]);
    
    int ret=0;
    while(pq.size()>1)
    {
        int min1=pq.top(); pq.pop();
        int min2=pq.top(); pq.pop();
        pq.push(min1+min2);
        ret+=min1+min2;
    }
    
    return ret;
}

int main(void)
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>n;
        
        vector<int> lengths(n);
        for(int i=0;i<n;++i)
            cin>>lengths[i];
        
        cout<<getMinSum(lengths)<<endl;
    }
    
    return 0;
}
