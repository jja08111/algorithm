#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int people_num;
vector<int> withdrawTime;

int getMinTime()
{
    int ret=0;
    sort(withdrawTime.begin(),withdrawTime.end());
    for(int i=0;i<people_num;++i)
    {
        int multiply_num=people_num-i;
        ret+=multiply_num*withdrawTime[i];
    }
    return ret;
}

int main()
{
    cin>>people_num;
    for(int i=0;i<people_num;++i)
    {
        int tmp;
        cin>>tmp;
        withdrawTime.push_back(tmp);
    }
    
    cout<<getMinTime()<<endl;
    
    return 0;
}
