# 해결 
문제에서 주어진 알고리즘을 잘 읽고 그대로 구현하면 되는 문제이다.  
주의할 점은 **"4-4. u의 첫 번째와 마지막 문자를 제거하고, 나머지 문자열의 괄호 방향을 뒤집어서 뒤에 붙입니다."** 를 algorith의 mreverse함수로 순서를 뒤집는 것이 아니라  
( 이면 )으로, )이면 (으로 변환하는 것이다.  
```c++
#include <string>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;

bool isCorrect(const string& s) {
    stack<char> opening;
    for(int i=0;i<s.size();++i) {
        if(s[i]=='(')
            opening.push('(');
        else {
            if(opening.empty())
                return false;
            opening.pop();
        }
    }
    return opening.empty();
}

string reverse(string s) {
    for(int i=0;i<s.size();++i)
        s[i]=(s[i]=='(') ? ')' : '(';
    return s;
}

string solution(string p) {
    // 빈 문자열 혹은 올바른 괄호 문자열인 경우 그대로 반환
    if(p.empty() || isCorrect(p))
        return p;
    
    // 문자열을 균형잡힌 괄호 문자열로 앞 뒤 나눈다.
    int idx=0, diff=0;
    while(idx!=p.size()) {
        diff+=(p[idx]=='(') ? 1 : -1;
        ++idx;
        if(diff==0)
            break;
    }
    
    string first=p.substr(0,idx);
    string second=p.substr(idx);
    
    if(isCorrect(first)) 
        return first+solution(second);
    
    string back=first.substr(1,first.size()-2);
    return "("+solution(second)+")"+reverse(back);
}
```
