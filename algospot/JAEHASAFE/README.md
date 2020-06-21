# 해결 
### 느린 구현
처음에는 기존 문자열 original에서 목표 문자열 target으로 만들이 위해 두 문자열을 오버랩 했다.  
그 후 오버랩 된 부분을 지운 나머지가 같으면 쉬프트 성공이라고 생각해 구현했다.  
(하지만 예제들은 통과 했으나 답안은 틀렸다고 나왔었다.)  

디버깅에 성공했다. 바로 두 문자열의 오버랩 된 부분외의 문자열이 같지 않았을 때의 처리를 하지 않았기 때문에 오류를 발생시킨 것이다.
3  
aabaa  
aaaba  
aaaba  
aabaa  

위와 같은 입력이 들어올 경우 실패했을 때 다음 칸으로 넘어가는 처리를 하지 않으면 오류를 발생시킨다.  
그러나 이 방법은 substr을 이용하기 때문에 느리다.  
```c++
// 느린답안
int minOverlap(const string& a, const string& b)
{
    int n=a.size(), m=b.size();
    vector<int> pi=getPartialMatch(b);
    int begin=0, matched=0;
    while(begin<n)
    {
        if(matched<m && a[begin+matched]==b[matched])
        {
            matched++;
            if(begin+matched==n)
            {
                string p=a.substr(0,n-matched);
                string q=b.substr(matched,m-matched);
                // 일치하면 종료한다.
                if(p==q)
                    return begin;
                // 실패했을 때 다음 칸으로 넘어간다.
                begin++;
                matched=0;
            }
        }
        else
        {
            if(matched==0)
                begin++;
            else
            {
                begin+=matched-pi[matched-1];
                matched=pi[matched-1];
            }
        }
    }
    return -INF;
}
```
### 문자열이 반복되는 점을 이용하자 
original을 두 개 이어서 만든 문자열내에서 target을 탐색해 위치를 반환하면 시계 반대방향쪽으로 몇번 돌려야 하는지 아주 쉽게 구할 수 있다.  
```c++
int shifts(const string& original, const string& target)
{
    return kmpSearch(original+original,target);
}
```
이때 시계 방향을 구하고 싶을 때는 메개변수의 순서를 바꾸면 된다. 
