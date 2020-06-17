#include <iostream>
#include <list>
using namespace std;

void josephus(int n, int k)
{
    list<int> soldier;
    for(int i=1;i<=n;++i)
        soldier.push_back(i);
    
    list<int>::iterator kill=soldier.begin();
    while(n>2)
    {
        kill=soldier.erase(kill);
        if(kill==soldier.end())
            kill=soldier.begin();
        n--;
        for(int i=0;i<k-1;++i)
        {
            kill++;
            if(kill==soldier.end())
                kill=soldier.begin();
        }
    }
    cout<<soldier.front()<<" "<<soldier.back()<<endl;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int n,k;
        cin>>n>>k;
        
        josephus(n,k);
    }
    return 0;
}
