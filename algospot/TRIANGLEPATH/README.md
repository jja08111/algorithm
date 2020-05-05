# 해결
이 문제를 해결하기 위한 메모이제이션 방법은 2가지가 있다.
- 재귀함수를 이용한 top-down방식
- 반복문을 이용한 bottom-up방식

### 재귀함수 이용
직관적으로 코드를 작성할 수 있는 방법이다.

위에서부터 아래로 내려가며 기저사례 도달하면 최적해를 구하는 방식이다.

전체 문제를 현재 위치(y,x) 일때 최대 경로 합을 구하는 부분 문제로 나누어 메모이제이션을 할 수 있다.
```c++
int path(int y, int x)
{
    //기저사례:마지막 라인에 도달한 경우
    if(y==n-1)
        return map[y][x];
    
    int& ret=cache[y][x];
    if(ret!=-1)
        return ret;
    
    return ret=map[y][x]+max(path(y+1,x),path(y+1,x+1));
}
```
### 반복문 이용
기저사례를 먼저 계산하여 밑에서부터 얻어낸 결과물로 위로 올라가는 방식이다.

재귀함수보다는 비직관적이다.

```c++
int iterative(void)
{
    //기저사례를 계산한다.
    for(int i=0;i<n;++i)
        cache[n-1][i]=map[n-1][i];
    
    //나머지를 계산한다.
    for(int y=n-2;y>=0;--y)
        for(int x=0;x<y+1;++x)
            cache[y][x]=max(cache[y+1][x],cache[y+1][x+1])+map[y][x];

    return cache[0][0];
}
```
슬라이딩 윈도(sliding window)기법을 이용하여 공간복잡도를 줄일 수 있다.

슬라이딩 윈도는 새 값을 계산할 때 과거에 계산한 결과가 전부 필요한 것이 아니라 일부분일때 이용 가능하다.

2줄에 저장해 한줄씩 옮겨가며 결과를 구한다.
```c++
int cache[2][100];
int iterative(void)
{
    for(int i=0;i<n;++i)
        cache[(n-1)%2][i]=map[n-1][i];
    
    for(int y=n-2;y>=0;--y)
        for(int x=0;x<y+1;++x)
            cache[y%2][x]=max(cache[(y+1)%2][x],cache[(y+1)%2][x+1])+map[y][x];

    return cache[0][0];
}
```
