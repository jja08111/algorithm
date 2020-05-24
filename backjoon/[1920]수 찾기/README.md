# 해결 
입력의 값이 많기 때문에 빠른 탐색 방법을 이용해야 한다.  
따라서 binary_search를 이용할 것이다. 
여기서 유의할 점은 수를 입력 받을때 빠른 입력함수를 이용해야한다.  
그렇지 않으면 시간초과가 발생한다.  

아래 함수는 인덱스를 찾아 가며 없으면 반으로 나누고 찾으면 참을 반환한다.  
```c++
bool findNum(int a)
{
    int lo=0, hi=n-1;
    while(hi>=lo)
    {
        int mid=(lo+hi)/2;
        
        if(num[mid]==a)
            return true;
        
        // 찾으려는 값보다 num[mid]값이 크다면 왼쪽으로 이동
        if(num[mid]>a)
            hi=mid-1;
        // 작다면 쪽으로 이동
        else 
            lo=mid+1;
    }
    return false;
}
```
