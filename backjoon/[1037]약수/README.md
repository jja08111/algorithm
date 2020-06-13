# 해결 
약수들이 주어졌을 때 최소 공배수를 찾는 문제이다.  
정렬을 하고 나서 가장 큰 약수와 작은 약수를 곱하여 간단하게 해결 할 수도 있다.  
```c++
int solve(int n, int num[50])
{
    sort(num,num+n);
    
    return num[0]*num[n-1];
}
```
