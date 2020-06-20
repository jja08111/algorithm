# 해결 
무식한 방법으로는 모든 부분 수열을 찾으며 부분 수열의 합이 k가 되는 구간을 전부 세는 것이다.  
하지만 이 방법으로는 도저히 해결할 수 없는 양이다.  

여기서 해결의 중요한 핵심은 head에서 tail까지 이루어진 구간에서 구간합이 k가 넘어가면 tail을 유지한 채 head를 늘려나가는 것이다.  
즉, 부분 합이 k를 넘어가면 그 head에서 시작하는 구간은 그만 찾는 것이다.  

### 온라인 알고리즘 
그런데 또 다른 문제에 마주하게 된다. 바로 메모리 부족이다.  
많은 양의 데이터를 전부 배열에 저장할 수는 없다.  
이를 해결하기 위해 온라인 알고리즘을 사용하면 된다.  
메모리에 저장하는 것은 현재 사용하는 구간만 저장한채 필요없는 부분은 버리는 방식이다.  

새로운 newSignal을 tail에 추가하다가 합이 k를 넘어서거나 같아지면 멈추고 head를 제거하는 방법으로 구현하면 된다.  
이때 생각나는 자료구조가 있는데 바로 queue이다.  
```c++
int countRange(int k, int n)
{
    RNG rng;
    queue<int> range;
    int ret=0, rangeSum=0;
    for(int i=0;i<n;++i)
    {
        int newSignal=rng.next();
        rangeSum+=newSignal;
        range.push(newSignal);
        
        while(rangeSum>k)
        {
            rangeSum-=range.front();
            range.pop();
        }
        
        if(rangeSum==k)
            ret++;
    }
    return ret;
}
```

### 난수 생성기 
이 문제는 직접 입력을 생성해 나가야 한다.  
클래스로 구현함으로서 간결한 코드를 만들 수 있다.  
이때 눈여겨 볼 부분은 unsigned 자료형을 사용함으로써 2^32로 나눈 나머지를 취하지 않아도 된다는 점이다.  
```c++
vstruct RNG {
    unsigned seed;
    RNG() : seed(1983) {}
    unsigned next() {
        unsigned ret=seed;
        seed=((seed*214013u)+2531011u);
        return ret%10000+1;
    }
};
```
