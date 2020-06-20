#include <iostream>
#include <string>
#include <stack>
using namespace std;

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

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        string brackets;
        cin>>brackets;
        
        if(isWellMatched(brackets))
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }
    
    return 0;
}
