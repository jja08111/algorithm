# 해결 
이진 탐색 트리를 구현하여 모든 값들을 넣은 후 k번째 값을 찾는 방식을 이용할 수 있다.  
하지만 직접 구현하는 것보다 훨씬 간단한 방법이 있다.  
바로 우선순위 큐를 이용하여 값들을 큰 값과 작은 값 두 가지로 분류하는 것이다.  

### 두 개의 힙 이용
우선순위 큐는 top()함수를 이용하여 쉽게 제일 큰 값과 작은 값에 접근할 수 있다.  
만약 작은 값들의 집합의 top()이 큰 값들의 집합의 top()보다 크면 그 두 값들을 교체하면 된다.  

- maxHeap: 중간 값과 같거나 작은 값들을 내림차순으로 저장
- minHeap: 중간 값보다 큰 값들을 오름차순으로 저장

중간 값은 원소의 수가 짝수일때 두 값 중 보다 작은 것이니 항상 maxHeap의 크기를 minHeap과 같거나 하나 더 크게 설정하면 된다.  
위 두 가지의 priority_queue를 만들고 조건을 만족하는 불변식을 설정하면 된다.  
```c++
int runningMedian(int n, RNG rng)
{
    //중간값과 같거나 작은 값들을 내림차순으로 저장
    //top에는 제일 큰 값이 있다.
    priority_queue<int, vector<int>, less<int> > maxHeap;
    //중간값보다 큰 값들을 오름차순으로 저장
    //top에는 제일 작은 값이 있다.
    priority_queue<int, vector<int>, greater<int> > minHeap;
    int ret=0;
    
    //반복문 불변식:
    //1.maxHeap의 크기는 minHeap의 크기와 같거나 1 더 크다.
    //2.maxHeap.top() <= minHeap.top()
    for(int cnt=1;cnt<=n;++cnt)
    {
        if(maxHeap.size()==minHeap.size())
            maxHeap.push(rng.next());
        else
            minHeap.push(rng.next());
        
        if(!minHeap.empty() && !maxHeap.empty() && 
            minHeap.top()<maxHeap.top())
        {
            int a=maxHeap.top(), b=minHeap.top();
            maxHeap.pop(); minHeap.pop();
            maxHeap.push(b);
            minHeap.push(a);
        }
        ret=(ret+maxHeap.top())%MOD;
    }
    return ret;
}
```

### 수열 생성하기
구조체를 이용하여 난수 생성기를 구현할 수 있다. 여기서 long long 형을 캐스팅하여 오버플로를 방지한 것을 볼 수 있다.
```c++
struct RNG {
    int seed,a,b;
    RNG(int _a, int _b) : a(_a), b(_b), seed(1983) {}
    int next() {
        int ret=seed;
        seed=((seed*(long long)a)+b)%MOD;
        return ret;
    }
};
```
