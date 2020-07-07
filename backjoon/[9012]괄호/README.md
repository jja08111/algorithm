# 해결 
문자열에서 열린 괄호의 수가 동일한 경우에만 VPS가 된다.  
중간에 닫힌 괄호가 더 많게 되는 경우는 무조건 VPS가 되지 않기 때문에 바로 false를 반환하였다.  
```c++
bool isVPS(const string& s)
{
    int opening=0;
    const int n=s.size();
    for(int i=0;i<n;++i)
    {
        if(opening<0)
            return false;
        
        if(s[i]=='(')
            ++opening;
        else
            --opening;
    }
    return opening==0;
}
```
