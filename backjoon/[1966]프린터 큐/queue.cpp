#include <iostream>
#include <queue>
using namespace std;

int getOrder(priority_queue<int>& priority, queue<pair<int,int> >& document, int n, int m)
{
    int count=1;
    while(1)
    {
        if(priority.top()==document.front().second)
        {
            if(document.front().first==m)
                return count;
            priority.pop();
            document.pop();
            count++;
        }
        else
        {
            pair<int,int> tmp=document.front();
            document.pop();
            document.push(tmp);
        }
    }
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        priority_queue<int> priority;
        // <index,priority>
        queue<pair<int,int> > document;
        int n,m;
        
        cin>>n>>m;
        for(int i=0;i<n;++i)
        {
            int p; 
            cin>>p;
            priority.push(p);
            document.push(make_pair(i,p));
        }
        cout<<getOrder(priority,document,n,m)<<endl;
    }
    
    return 0;
}
