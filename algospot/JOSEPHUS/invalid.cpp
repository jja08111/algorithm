#include <iostream>
#include <list>
using namespace std;

int n,k;

void josephus()
{
    list<int> soldier;
    for(int i=1;i<n;++i)
        soldier.push_back(i);
    
    soldier.pop_front();
    list<int>::iterator iter=soldier.begin();
    int count=1;
    while(soldier.size()>2)
    {
        if(iter==soldier.end())
            iter=soldier.begin();
        if(count==k)
        {
            soldier.erase(iter);
            count=0;
        }
        iter++;
        count++;
    }
    cout<<soldier.front()<<soldier.back()<<endl;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>n>>k;
        
        josephus();
    }

    return 0;
}
