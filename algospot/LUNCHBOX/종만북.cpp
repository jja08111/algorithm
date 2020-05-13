#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int n;

int getMinTime(vector<int>& heat, vector<int>& eat)
{
    vector<pair<int,int> > order;
    for(int i=0;i<n;++i)
        order.push_back(make_pair(-eat[i],i));
    sort(order.begin(),order.end());
    
    int ret=0, beginEat=0;
    for(int i=0;i<n;++i)
    {
        int box=order[i].second;
        beginEat+=heat[box];
        ret=max(ret,beginEat+eat[box]);
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
        
        vector<int> heat(n),eat(n);
        
        for(int i=0;i<n;++i)
            cin>>heat[i];
        for(int i=0;i<n;++i)
            cin>>eat[i];
        
        cout<<getMinTime(heat,eat)<<endl;
    }
    return 0;
}
