# 해결
이 문제는 손으로 풀다보면 회의가 끝나는 시간으로 정렬해야 한다는 직감이 온다.  
그 후 끝나는 시간이 같다면 시작하는 시간으로 정렬한다.  
정렬한 값의 앞에서부터 이용 가능하면 결과에 추가한다.  

반례로 회의가 더 늦게 끝나는 값을 먼저 이용한다고 생각해면 위의 내용이 최적해인것을 알 수 있다.

### priority_queue 이용 
위의 내용을 쉽게 구현하기 위해서 priority_queue를 이용했다.  
주의할 점은 습관처럼 <>안에 int로 오인하여 작성하지 말아야 한다.  
```c++
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
```
