#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n;
    cin>>n;
    //오름차순 저장  
    priority_queue<int, vector<int>, greater<int> > pq;
    while(n--)
    {
        int x;
        scanf("%d",&x);
        
        if(x==0)
        {
            if(pq.empty())
                printf("0 \n");
            else
            {
                printf("%d \n",pq.top());
                pq.pop();
            }
        }
        else
            pq.push(x);
    }
    return 0;
}
