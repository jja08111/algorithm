# 해결
스택을 이용하면 간단히 해결할 수 있으나 몇가지 유의할 부분이 있다.  
1. 입력이 "(" 만 들어올 경우를 대비해 마지막 리턴값을 '남은 열린 괄호가 비워졌는지'로 한다.
2. 입력이 ")" 일 경우 또한 고려하여 처리해야 한다.  

열린 괄호와 닫힌 괄호들의 짝을 문자열로 구현해 놓고 find함수를 이용하면 간결하게 구현할 수 있다.  
find함수는 찾고자하는 문자의 위치를 반환하고 없을 경우 npos를 반환한다.  
```c++
bool isWellMatched(string& brackets)
{
    const string opening("({["), closing(")}]");
    stack<char> openStack;
    int n=brackets.size();
    for(int i=0;i<n;++i)
    {
        if(opening.find(brackets[i])!=-1)
            openStack.push(brackets[i]);
        else
        {
            if(openStack.empty())
                return false;
            if(opening.find(openStack.top()) != closing.find(brackets[i]))
                return false;
            openStack.pop();
        }
    }
    return openStack.empty();
}
```
