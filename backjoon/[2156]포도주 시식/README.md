# 해결 
메모이제이션을 이용하여 해결했다.  
현재 포도주를 마시거나 마시지 않는 2가지의 경우를 재귀하였다.  
이때 현재 어느 포도주인지, 몇잔째 연속되었는지를 메모이제이션 하는 것이 중요하다.  
따라서 기저사례로 연속으로 3잔이 되었을때 음의 무한대를 반환하는 것을 설정해야 한다.  
```c++
int n,wine[MAX];
int cache[MAX][3];

int solve(int here, int continues)
{
    if(continues==3)
        return -987654321;
    if(here==n)
        return 0;
    
    int& ret=cache[here][continues];
    if(ret!=-1)
        return ret;
    
    return ret=max(solve(here+1,0), solve(here+1,continues+1)+wine[here]);
}
```
