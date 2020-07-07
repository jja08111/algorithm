#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void printMidnum(const int n)
{
    priority_queue<int, vector<int>, less<int> > maxHeap;
    priority_queue<int, vector<int>, greater<int> > minHeap;
    
    for(int i=0;i<n;++i)
    {
        int num;
        scanf("%d",&num);
        
        if(maxHeap.size()==minHeap.size())
            maxHeap.push(num);
        else
            minHeap.push(num);
        
        if(!maxHeap.empty() && !minHeap.empty() && maxHeap.top()>minHeap.top())
        {
            int a=maxHeap.top(), b=minHeap.top();
            maxHeap.pop(); minHeap.pop();
            maxHeap.push(b);
            minHeap.push(a);
        }
        printf("%d\n",maxHeap.top());
    }
}

int main()
{
    int n;
    cin>>n;
    
    printMidnum(n);
    
    return 0;
}
