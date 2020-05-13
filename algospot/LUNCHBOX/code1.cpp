#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int n;

int getMinTime(vector<pair<int,int> >& food)
{
    sort(food.begin(), food.end());
    int heatingTime=food[0].second;
    int remainingEat=food[0].first;
    
    for(int i=1;i<n;++i)
    {
        heatingTime+=food[i].second;
        //데웠던 시간을 빼준다.
        remainingEat+=food[i].second;
        remainingEat=min(remainingEat,food[i].first);
    }
    
    return heatingTime-remainingEat;
}

int main(void)
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>n;
        
        vector<int> heat(n),eat(n);
        vector<pair<int,int> > food;
        
        for(int i=0;i<n;++i)
            cin>>heat[i];
        for(int i=0;i<n;++i)
            cin>>eat[i];
        //역순으로 정렬하기 위해 음수를 취해준다.
        for(int i=0;i<n;++i)
            food.push_back(make_pair(-eat[i],heat[i]));
        
        cout<<getMinTime(food)<<endl;
    }
    return 0;
}
