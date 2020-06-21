# 해결 
접두사와 접미사가 같아야 한다는 부분에서 [KMP알고리즘](https://bowbowbow.tistory.com/6)을 떠올릴 수 있다.  

합친 문자열 S의 부분 일치 테이블 pi[]를 만들어 이를 응용하는 것이 핵심이다.  
전체 문자열은 접두사도 되고 접미사도 되니 포함 시킨 뒤, 전체 문자열 길이 k에 대한 p[k-1]를 찾으면 k 다음으로 긴 접미사를 찾을 수 있다.  
```c++
vector<int> getPartialMatch(const string& s)
{
    int n=s.size();
    vector<int> pi(n,0);
    int begin=1, matched=0;
    while(begin+matched<n)
    {
        if(s[matched]==s[begin+matched])
        {
            matched++;
            pi[begin+matched-1]=matched;
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
    return pi;
}

vector<int> getPrefixSuffix(const string& s)
{
    vector<int> ret, pi=getPartialMatch(s);
    int k=s.size();
    while(k>0)
    {
        ret.push_back(k);
        k=pi[k-1];
    }
    return ret;
}
```
