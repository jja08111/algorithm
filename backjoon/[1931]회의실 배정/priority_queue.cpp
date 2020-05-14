#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

typedef pair<int,int> Pair;

int solve(priority_queue<Pair,vector<Pair>,greater<Pair> >& pq)
{
    int ret=0, prevEnd=0;
    while(!pq.empty())
    {
        //현재 회의가 이전 회의와 겹치지 않아야 한다.
        if(prevEnd<=pq.top().second)
        {
            ++ret;
            prevEnd=pq.top().first;
        }
        pq.pop();
    }
    
    return ret;
}

int main(void)
{
    int n;
    cin>>n;
    
    priority_queue<Pair,vector<Pair>,greater<Pair> > pq;
    for(int i=0;i<n;++i)
    {
        int start,end;
        cin>>start>>end;
        //회의가 끝나는 순으로 우선순위를 둔다.
        pq.push(make_pair(end,start));
    }
    
    cout<<solve(pq);
    
    return 0;
}
