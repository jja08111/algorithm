# 해결 
[KMP알고리즘](https://github.com/jja08111/algorithm/blob/master/algospot/20%20%EB%AC%B8%EC%9E%90%EC%97%B4/2%20%EB%AC%B8%EC%9E%90%EC%97%B4%20%EA%B2%80%EC%83%89/KMP.cpp)을 
이용하여 해결했다.  
KMP알고리즘을 간단히 설명하자면 문자열 H에서 N을 찾으려고 할 때 중복되어 찾는 부분을 없애 찾는 속도를 향상시키는 알고리즘이다.  
문자열 N이 aabaaba와 같이 접미사와 접두사가 중복되거나 또는 접두사 aabaa에서 접미사와 접두사가 겹치는 부분을 찾아내어 일치한 부분을 건너뛰는 대신 겹치는 부분부터 다시 탐색하는 방식이다.  
```c++
vector<int> getPartialMatch(const string& s)
{
    int n=s.size();
    vector<int> ret(n,0);
    int begin=1, matched=0;
    while(begin+matched<n)
    {
        if(s[begin+matched]==s[matched])
        {
            ++matched;
            ret[begin+matched-1]=matched;
        }
        else
        {
            if(matched==0)
                ++begin;
            else
            {
                begin+=matched-ret[matched-1];
                matched=ret[matched-1];
            }
        }
    }
    return ret;
}

vector<int> KMPsearch(const string& T, const string& P)
{
    int n=T.size(), m=P.size();
    vector<int> ret;
    vector<int> pi=getPartialMatch(P);
    int begin=0, matched=0;
    while(begin<=n-m)
    {
        if(matched<m && T[begin+matched]==P[matched])
        {
            ++matched;
            if(m==matched)
                ret.push_back(begin+1);
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
    return ret;
}
```
