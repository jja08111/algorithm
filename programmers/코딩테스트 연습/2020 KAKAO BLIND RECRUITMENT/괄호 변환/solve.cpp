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
