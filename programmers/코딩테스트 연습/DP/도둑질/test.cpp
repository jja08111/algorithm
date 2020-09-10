#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int MAX_N=1000001;

// [house]
int cache[MAX_N];

int showMeTheMoney(vector<int>& money, int house, bool visitedFirst) {
    if((visitedFirst && house>=money.size()-1) || 
        (!visitedFirst && house>=money.size()))
        return 0;
    
    int& ret=cache[house];
    if(ret!=-1)
        return ret;
    
    return ret=max(money[house]+showMeTheMoney(money, house+2, visitedFirst), 
                   showMeTheMoney(money,house+1,visitedFirst));
}

int solution(vector<int> money) {
    memset(cache,-1,sizeof(cache));
    int ret=showMeTheMoney(money,0,true);
    memset(cache,-1,sizeof(cache));
    ret=max(ret,showMeTheMoney(money,1,false));
    return ret;
}

int main()
{
    int n;
    cin>>n;
    vector<int> money(n);
    for(int i=0;i<n;++i)
        cin>>money[i];
    
    cout<<solution(money);
    
    return 0;
}
