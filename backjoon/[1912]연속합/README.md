# 해결 
재귀적으로 해결했다. 손으로 풀어보면 알 수 있는데 n+1번째 숫자로 시작하는 수열의 최대값이 음수라면 n번째 수열과 더할 필요가 없다.  
즉, 다음 숫자에서 시작하는 수열의 합 중 최대값이 음수라면 무시하는 방식이다.  
점화식으로 나타내면 아래와 같다.  
- sum[χ] = max(sum[χ - 1] + χ, χ)

다음 코드에서 눈여겨 볼 점은 answer라는 전역 변수를 이용해서 별도의 반복문을 구현하지 않아도 된다는 것이다. 
```c++
int n,seq[MAX];
int answer=NAG_INF;

int solve(int start)
{
    if(start==n)
        return 0;
    
    //현재 숫자를 포함한다.
    int ret=seq[start];
    //다음 숫자부터 시작하는 수열들 중 최대합을 찾는다.
    int next=solve(start+1);
    //다음 수열이 음수인 경우 포함하지 않는다.
    ret+=max(0,next);
    
    //최대값을 전역변수에 저장하여 따로 반복문을 만들지 않는다.
    answer=max(answer,ret);
    
    return ret;
}
```
반복문으로 구현하면 아래와 같다. 더욱 효율적이다.
```c++
void solve()
{
    int answer=seq[0];
    int sum=seq[0];
    for(int i=1;i<n;i++) 
    {
        sum=max(sum+seq[i],seq[i]);
        answer=max(answer,sum);
    }
    cout<<answer;
}
```
