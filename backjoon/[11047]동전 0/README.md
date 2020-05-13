# 해결
직관적으로 보면, 동전의 갯수를 줄이기 위해 가치가 큰 동전부터 생성해 나가면 된다.  
```c++
for(int i=n-1;i>=0;--i)
    while(remain-coins[i]>=0)
    {
        remain-=coins[i];
        ++needs;
    }
```
