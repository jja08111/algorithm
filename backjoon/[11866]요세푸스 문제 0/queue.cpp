#include <iostream>
#include <queue>
using namespace std;

queue<int> survivor;

void josephus(int n, int k)
{
    cout<<'<';
    while(n>0)
    {
        for(int i=0;i<k-1;++i)
        {
            int tmp=survivor.front();
            survivor.pop();
            survivor.push(tmp);
        }
        cout<<survivor.front();
        survivor.pop();
        n--;
        if(n>0)
            cout<<", ";
    }
    cout<<'>'<<endl;
}

int main()
{
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;++i)
        survivor.push(i);
    
    josephus(n,k);
    
    return 0;
}
