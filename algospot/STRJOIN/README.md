# 해결
이 문제를 손으로 풀다보면 문자열 길이가 작은 것 2개를 합쳐나가야지 최솟값이 된다는 것을 알 수 있다.
따라서 아래와 같이 순서도를 생각할 수 있다.
- 문자열 길이를 오름차순으로 배열에 정렬한다.
- 맨 앞 2개의 값을 더하고 sum에 더한다.
- 2개의 값을 배열에서 제거하고 합한 값을 배열에 추가한다.
- 다시 오름차순으로 정렬한다.
- 값이 1개가 남을때 까지 계속한다.
## 구현
### 1. multiset 이용
multiset은 입력받는 값에 대해 균형 이진트리로 자동으로 정렬을 한다.  
이 부분을 이용하여 반복자로 구현한다.
```c++
int getMinSum(multiset<int>& lengths)
{
    int sum=0;
    while(lengths.size()>1)
    {
        multiset<int>::iterator iter=lengths.begin();
        
        int add=*(iter++);
        add+=*iter;
        sum+=add;
        
        lengths.erase(iter);
        lengths.erase(--iter);
        lengths.insert(add);
    }
    return sum;
}
```
### 2. priority_queue 이용
맨 앞 2개의 값을 빼낸다는 점을 생각하면 큐를 떠올릴 수 있다.  
그 중에서도 우선순위 큐가 적합할 것이다.  
작은 값을 빼내야 하니 비교 연산자를 greater로 해줬다.  
```c++
int getMinSum(const vector<int>& lengths)
{
    priority_queue<int,vector<int>,greater<int> > pq;
    for(int i=0;i<n;++i)
        pq.push(lengths[i]);
    
    int ret=0;
    while(pq.size()>1)
    {
        int min1=pq.top(); pq.pop();
        int min2=pq.top(); pq.pop();
        pq.push(min1+min2);
        ret+=min1+min2;
    }
    
    return ret;
}
```
