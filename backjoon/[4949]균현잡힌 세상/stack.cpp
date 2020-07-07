#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool isVPS(const string& s)
{
    const string opening="([", closing=")]";
    const int n=s.size();
    stack<char> opens;
    
    for(int i=0;i<n;++i)
    {
        string::size_type posOpen=opening.find(s[i]);
        string::size_type posClose=closing.find(s[i]);
        
        if(posOpen!=string::npos)
            opens.push(s[i]);
        else if(posClose!=string::npos)
        {
            if(opens.empty() || opening.find(opens.top())!=posClose)
                return false;
            opens.pop();
        }
    }
    return opens.empty();
}

int main()
{
    while(true)
    {
        string s;
        getline(cin,s,'.');
        getchar();
        if(s.empty())
            break;
        
        if(isVPS(s))
            cout<<"yes"<<endl;
        else
            cout<<"no"<<endl;
    }

    return 0;
}
