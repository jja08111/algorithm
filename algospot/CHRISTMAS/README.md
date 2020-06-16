# 해결 
이 문제를 읽고 부분합을 이용해 H에서 T까지 구입 했을 때 남기지 않고 어린이들에게 나눠줄 수 있는지를 수식으로 나타내면 아래와 같다.  
- (psum[T]-psum[H-1]) mod children=0

이 식을 살짝 변형하면 아래처럼 된다.
- psum[T] mod children=psum[H-1] mod children

### 첫 번째 질문
즉 psum을 생성할 때 어린이들 수로 나눈 나머지들로 저장하여 두고, psum의 원소가 같은 것들이 2개라면 하나의 주문을 만들 수 있다.  
따라서 숫자 i가 psum에 출현하는 횟수를 f(i)라고 할때 총 주문 횟수는 아래와 같다.  
- (j=0 ~ k-1)Σ ((f(i) * (f(i) - 1)) / 2)
```c++
int wayToBuy(const vector<int>& psum, int children)
{
    int ret=0;
    //psum의 값을 몇 번이나 본 적 있는지 기록한다.
    vector<long long> count(children,0);
    for(int i=0;i<psum.size();++i)
        count[psum[i]]++;
    //두 번 이상 본 적 있다면 이값 중 두 개를 선택하는 방법의 수를 더한다.
    for(int i=0;i<children;++i)
        if(count[i]>=2)
            ret=(ret+((count[i]*(count[i]-1))/2))%MOD;
    return ret;
}
```

### 두 번째 질문
먼저 i번째 상자를 고르거나 고르지 않는 재귀함수를 구현하고 여기에 메모이제이션을 적용하여 해결할 수 있다.  
- 고르지 않는 경우 i-1번째의 결과가 적용된다.  
- 고르는 경우는 psum[j-1]=psum[i]일 때이다. 이 때 j가 여러개인 경우 가장 오른쪽의 j를 골라 가능한 구간의 수를 최대화 할 수 있다.  
여기서 이전에 psum의 값이 나온 위치를 계속 갱신해 나가는 것으로 구현할 수 있다.  
```c++
int maxBuys(const vector<int>& psum, int children)
{
    //ret[i]=첫 번째 상자부터 i번째 상자까지 고려했을 때 살 수 있는 최대 횟수
    vector<int> ret(psum.size(),0);
    //prev[s]=psum[]이 s였던 마지막 위치
    vector<int> prev(children,-1);
    for(int i=0;i<psum.size();++i)
    {
        //i번째 상자를 전혀 고려하지 않음
        if(i>0)
            ret[i]=ret[i-1];
        else
            ret[i]=0;
        //psum[i]를 전에도 본 적이 있으면, prev[psum[i]]+1부터 여기까지 쭉 사본다.
        int location=prev[psum[i]];
        if(location!=-1)
            ret[i]=max(ret[i],ret[location]+1);
        //prev[]에 현재 위치를 기록한다.
        prev[psum[i]]=i;
    }
    return ret.back();
}
```

### psum 생성시 주의사항
첫 번째 질문에서 (H-1)인덱스를 확인할때 처럼 psum의 원소를 확인해야 하는 경우가 있다.  
따라서 예외처리를 간단하게 하기 위해 가상의 0의 값을 추가하여 구현을 편하게 하였다.  
```c++
vector<int> getPartialSum(const vector<int>& a, int children)
{
    int n=a.size();
    vector<int> ret(n+1);
    ret[0]=0;
    for(int i=1;i<=n;++i)
        //가상의 0값을 넣었으니 a[i-1]을 더해 나간다.
        ret[i]=(ret[i-1]+a[i-1])%children;
    return ret;
}
```
