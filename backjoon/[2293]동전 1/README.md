# 해결

https://aerocode.net/105
http://blog.naver.com/occidere/220793012348

## 시도 1
주요내용을 정리하면
- 재귀함수로 구현하여 메모이제이션을 이용하면 이전의 조합내용이 중복되는 경우가 발생한다. 이를 막기위해 메모이제이션에 추가로 범위를 부여하면 메모리제한에 걸리게 된다.
```C++
int n,k;
int cost[100],cache[100][100001];

int count(int here, int remain)
{
    if(remain==0)
        return 1;
    
    int& ret=cache[here][remain];
    if(ret!=-1)
        return ret;
    
    ret=0;
    for(int next=here;next<n;++next)
        if(remain>=cost[next])
            ret+=count(next,remain-cost[next]);
    
    return ret;
}
```

## 시도 2
결국 재귀함수를 변경하여 답을 도출하고 싶었으나 나의 머리로는 불가능했다.

인터넷을 찾아보니 중요한 내용이 몇가지 있었다.

