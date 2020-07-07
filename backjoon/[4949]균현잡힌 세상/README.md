# 해결 
stack의 LAST IN FIRST OUT 인 성질을 이용하여 이 문제를 해결할 수 있다.  

아래 코드에서 열린 괄호들의 집합을 만들어서 코드를 간결화 한 것을 눈여겨 볼 수 있다.   
유의할 점은 열린 괄호가 하나도 없는 상태에서 바로 닫힌 괄호가 입력되었을때의 처리를 잊으면 안되는 것이다.  
```c++
bool isVPS(const string& s)
{
    const string opening="([", closing=")]";
    const int n=s.size();
    stack<char> opens;
    
    for(int i=0;i<n;++i)
    {
        string::size_type posOpen=opening.find(s[i]);
        string::size_type posClose=closing.find(s[i]);
        
        //열린 괄호인 경우
        if(posOpen!=string::npos)
            opens.push(s[i]);
        //닫힌 괄호인 경우
        else if(posClose!=string::npos)
        {
            //열린 괄호가 없거나 열린 괄호와 매칭이 안되는 경우
            if(opens.empty() || opening.find(opens.top())!=posClose)
                return false;
            opens.pop();
        }
    }
    return opens.empty();
}
```
