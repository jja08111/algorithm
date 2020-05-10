# 해결
### 1. 무식한 방법

처음에는 천만이라는 숫자에 압도당했다.  
그로인해 (메모리의 총합)-(필요한 메모리)를 계산하여 최대 리프레시비용을 얻어 리프레시 총합에서 빼려고 했다.  
한마디로 총합에서 최대치를 빼는 방법이었다.  
이 방법은 공간,시간복잡도에서 굉장히 나쁜 방법이었다.

### 2. 발상의 전환

- 리프레시비용의 합은 10000보다 작다.
- 따라서 c[a]=b 에서 a를 메모리로 잡고 b를 리프레시비용의 합으로 하지 않고 거꾸로 c[b]=a처럼 한다.
- c의 모든 값을 탐색하며 메모리가 need보다 큰 값중 가장 작은 idx를 찾는다.
```c++
void calcMemory(void)
{
    for(int idx=0;idx<n;++idx)
        for(int cost=sum; cost>=refreshCost[idx]; --cost)
            c[cost]=max(c[cost],c[cost-refreshCost[idx]]+usingMemory[idx]);
}
int getMinCost(void)
{
    for(int i=0;i<sum;++i)
        if(c[i]>=need)
            return i;
}
```

# 회고
반복문을 증가식으로 구현했었는데 이렇게 하면 같은 index를 중복되어서 계산한다.  
```c++
for(int cost=refreshCost[idx]; cost<=sum; ++cost)
```
따라서 아래처럼 감소식으로 구현해야 한다.
```c++
for(int cost=sum; cost>=refreshCost[idx]; --cost)
```
