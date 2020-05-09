# 해결
이전에 풀었던 "여행 짐 싸기"문제와 비슷하지만 다른점이 2가지 있다.  
- 각 물건들은 무한정 가져갈 수 있다.
- 가져갈 수 있는 총량의 제한이 엄청 크다.  

### 반복적 동적 계획법 
두번째가 문제인데 이는 반복적 동적 계획법을 이용하여 해결할 수 있다.  
(c[예산])을 계산하기 위해서는 (c[예산-접시가격]+선호도)를 반복적으로 계산하면 된다.  
코드로 구현하면 아래와 같다.  
```c++
int getMaxPrefer(void) {
    int ret=0;
    for(int budget=1;budget<=m;++budget) {
        c[budget]=0;
        for(int dish=0;dish<n;++dish)
            if(budget>=price[dish])
                c[budget]=max(c[budget],c[budget-price[dish]+prefer[dish]);
        ret=max(ret,c[budget]);
    }
    return ret;
}
```
### 슬라이딩 윈도  
메모리가 차지하는 것이 너무 크니 사용하지 않는 부분을 없애야 한다.  
따라서 슬라이딩 윈도 기법을 사용한다.  
- 가격은 100의 배수이니 100으로 나눈값을 저장한다.  
- 계산을 위해 필요한 값을 구하는데 c[budget-200]이전의 원소들은 필요가 없다.  
왜냐하면 초밥의 가격은 최대 20000/100=200원이기 때문이다.  

코드로 구현하면 아래와 같다.  
```c++
int getMaxPrefer(void) {
    int ret=0;
    c[0]=0;
    for(int budget=1;budget<=limit;++budget) {
        int cand=0;
        for(int dish=0;dish<n;++dish)
            if(budget>=price[dish])
                cand=max(cand,c[(budget-price[dish])%201]+prefer[dish]);
        c[budget%201]=cand;
        ret=max(ret,cand);
    }
    return ret;
}
```
# 회고 
반복적 동적 계획법은 직관적으로 답이 떠오르지 않는다.  
슬라이딩 윈도 또한 이해하기 어렵다.
