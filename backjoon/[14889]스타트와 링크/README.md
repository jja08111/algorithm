# 해결 
생각보다 해결하는데 오래 걸린 문제이다.  
이 문제의 핵심은 아래의 두 가지로 문제를 나누는 것이다.  
1. 팀의 조합 만들기
2. 만들어진 팀에서 스타트팀과 링크팀의 전력 차이 구하기 

팀의 조합은 0번 선수가 있는 팀과 없는 팀으로 나누어서 구하면 쉽게 구현할 수 있다.  
이때 DFS를 이용하여 팀이 만들어진 경우 전력 차이를 계산하여 현재까지 계산한 최소 전력 차이보다 작은지 확인한다.  
만약 이미 최소 전력 차이가 0 이라면 계산을 종료한다.

비트마스크로도 구현할 수 있으나 이 문제에서는 코드가 직관적이지 않고 속도 향상도 미비해서 추천하지 않는다.  
```c++
const int INF=987654321;

bool isSelected[20]; // 0번 선수는 true인 상태이다.
int n,ability[20][20];
int ret=INF;

void getMinDiff()
{
    int startAbility=0, linkAbility=0;
    
    for(int a=0;a<n;++a)
        for(int b=a+1;b<n;++b)
        {
            // a선수와 b선수가 start팀에 속하는 경우
            if(isSelected[a] && isSelected[b])
                startAbility+=(ability[a][b]+ability[b][a]);
            // a선수와 b선수가 link팀에 속하는 경우
            else if(!isSelected[a] && !isSelected[b])
                linkAbility+=(ability[a][b]+ability[b][a]);
        }
    
    ret=min(ret,abs(startAbility-linkAbility));
}

//
void solve(int here, int count)
{
    if(ret==0) return;
    // 선수 선택을 완료한 경우
    if(count==n/2)
    {
        getMinDiff();
        return;
    }
    
    // dfs
    for(int there=here+1;there<n;++there)
        if(!isSelected[there])
        {
            isSelected[there]=true;
            solve(there,count+1);
            isSelected[there]=false;
        }
}
```
