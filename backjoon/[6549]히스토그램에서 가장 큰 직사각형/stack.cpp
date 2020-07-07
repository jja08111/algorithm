#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> h;
int n;

long long getMaxArea()
{
    stack<int> remaining;
    h.push_back(-1);
    long long ret=0;
    for(int i=0;i<h.size();++i)
    {
        while(!remaining.empty() && h[remaining.top()]>=h[i])
        {
            int j=remaining.top();
            remaining.pop();
            int width=-1;
            
            if(remaining.empty())
                width=i;
            else
                width=(i-remaining.top()-1);
            ret=max(ret,(long long)width*h[j]);
        }
        remaining.push(i);
    }
    return ret;
}

int main()
{
    while(true)
    {
        cin>>n;
        if(n==0)
            break;
        
        h.clear();
        for(int i=0;i<n;++i)
        {
            int tmp;
            scanf("%d",&tmp);
            h.push_back(tmp);
        }
        cout<<getMaxArea()<<endl;
    }

    return 0;
}
