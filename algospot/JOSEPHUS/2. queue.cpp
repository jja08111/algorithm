#include <iostream>
#include <queue>
using namespace std;

int n,k;

void josephus(queue<int>& survivor)
{
    while(n>2)
    {
        survivor.pop();
        n--;
        for(int i=0;i<k-1;++i)
        {
            int tmp=survivor.front();
            survivor.pop();
            survivor.push(tmp);
        }
    }
    
    //오름차순으로 출력한다.
    if(survivor.front()>survivor.back())
        cout<<survivor.back()<<" "<<survivor.front()<<endl;
    else
        cout<<survivor.front()<<" "<<survivor.back()<<endl;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>n>>k;
        
        queue<int> survivor;
        for(int i=1;i<=n;++i)
            survivor.push(i);
        
        josephus(survivor);
    }
    
    return 0;
}
