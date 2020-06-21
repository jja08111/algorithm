# 해결 
입력 문자열 S의 접미사이며, S를 뒤집은 문자열 R의 접두사인 문자열의 길이가 가장 긴 것을 찾는 문제이다.  
즉, S와 R을 서로 겹쳐지는 부분이 얼마나 긴지 찾아내는 것이다. 

[KMP 알고리즘](https://bowbowbow.tistory.com/6)을 이용하여 겹치는 부분 일치 하면 그 값이 가장 큰 값이기에 바로 반환한다.  
그 후 S의 길이에 2배 값에 겹치는 부분을 빼면 원하는 결과가 나온다.  
```c++
vector<int> getPartialMatch(const string& s)
{
    int n=s.size();
    vector<int> pi(n,0);
    int begin=1, matched=0;
    while(begin+matched<n)
    {
        if(s[begin+matched]==s[matched])
        {
            ++matched;
            pi[begin+matched-1]=matched;
        }
        else
        {
            if(matched==0)
                ++begin;
            else
            {
                begin+=matched-pi[matched-1];
                matched=pi[matched-1];
            }
        }
    }
    return pi;
}

int maxOverlap(const string& a, const string& b)
{
    int n=a.size(), m=b.size();
    vector<int> pi=getPartialMatch(b);
    int begin=0, matched=0;
    while(begin<n)
    {
        if(matched<m && a[begin+matched]==b[matched])
        {
            ++matched;
            //문자열 a와 b가 서로 겹쳐진 부분이 일치 했을 때 
            if(begin+matched==n)
                return matched;
        }
        else
        {
            if(matched==0)
                ++begin;
            else
            {
                begin+=matched-pi[matched-1];
                matched=pi[matched-1];
            }
        }
    }
    return 0;
}
```
