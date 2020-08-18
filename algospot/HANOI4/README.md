# 해결 
간단하게 각 기둥에 꽂힌 원반의 번호를 네 개의 정수 배열로 표현할 수 있다.  
하지만 이는 크기가 너무 크며 객체를 복사하는 데 드는 비용이나 메모리가 너무 많이 사용된다.  

여기서 각 원반이 어떤 기둥에 꽂혀 있는지를 저장하는 것이다.  
기둥이 4개이니 2개의 비트로 표시 가능하고 비트 마스킹을 이용해 각 원반의 인덱스의 두 배 만큼 비트 연산하여 표현 가능하다.  
즉, 3개의 원반이 있고 각 기둥에 3 1 0 2 으로 꽂혀 있을 때 비트 마스킹을 하면 00 11 00 10 으로 표현할 수 있다.  

특정한 원반이 어떠한 기둥에 꽂혀 있는지 반환하고, 현재 꽂힌 원반을 원하는 위치에 옮긴 후 상태를 반환하는 함수를 비트마스킹을 이용하 만들 수 있다.  
```c++
// index원판이 어느 기둥에 들어있는지 반환
int get(int state, int index)
{
    return (state >> (index*2)) & 3;
}
// 현재 있던 index 원반을 제거 후, value 위치에 원반을 놓음
int set(int state, int index, int value)
{
    return (state & ~(3<<(index*2))) | (value << (index*2));
}

```

그리고 일반적인 BFS를 수행하기 보다는 시작과 끝 상태가 정해져 있고 그래프가 양방향 그래프이기 때문에 양방향 탐색을 적용하는 것이 좋다.  
정방향은 양수로 역방향은 음수로 거리를 표시하여 두 지점이 만나는 순간 두 값이 다르다면 가운데서 만났다고 할 수 있다.  

눈여겨 볼 부분은 모든 원반을 큰 원반부터 작은 원반 순으로 탐색하며 각 기둥의 맨 위에 어떤 원반이 있는지를 쉽게 찾을 수 있다는 것이다.
```c++
const int MAX_DISCS=12;

int sgn(int x)
{
    if(!x)
        return 0;
    return x>0 ? 1 : -1;
}

int incr(int x)
{
    if(x<0)
        return x-1;
    return x+1;
}

int c[1<<(MAX_DISCS*2)];

int bidir(int discs, int begin, int end)
{
    if(begin==end)
        return 0;
    
    queue<int> q;
    // 초기화를 0으로 하는 데 주의
    memset(c,0,sizeof(c));
    q.push(begin); c[begin]=1;
    q.push(end); c[end]=-1;
    
    while(!q.empty())
    {
        int here=q.front();
        q.pop();
        
        // 각 기둥의 맨 위에 어떤 원반이 있는지 계산한다.
        int top[4]={-1,-1,-1,-1};
        for(int i=discs-1;i>=0;--i)
            top[get(here,i)]=i;
        
        // i번 기둥 맨 위에 있는 원반을 j번 기둥으로 옮긴다.
        for(int i=0;i<4;++i)
            if(top[i]!=-1)
                for(int j=0;j<4;++j)
                    if(i!=j && (top[j]==-1 || top[j]>top[i]))
                    {
                        int there=set(here,top[i],j);
                        if(c[there]==0)
                        {
                            c[there]=incr(c[here]);
                            q.push(there);
                        }
                        else if(sgn(c[here])!=sgn(c[there]))
                            return abs(c[here])+abs(c[there])-1;
                    }
    }
    return -1;
}
```
