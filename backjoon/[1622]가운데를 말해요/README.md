# 해결 
주어주는 입력들을 반으로 나누어 큰 부분과 작은 부분으로 저장해 두면 실마리가 보인다.  
저장할 때에 작은 값들은 내림차순으로, 큰 값들은 오름차순으로 정렬하여 각각의 집합의 0번 인덱스가 서로 맞닿게 하면 문제를 쉽게 해결할 수 있다.   
수열의 개수가 짝수일 경우 더 작은 값을 사용하니 작은 값들의 집합을 1개 더 많거나 큰 값들과 개수를 같게 설정하면 된다.  

수열의 top에 쉽게 접근할 수 있고 자동으로 heap구조를 유지하는 우선순위 큐를 이용하면 알맞다.  
```c++
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
```
