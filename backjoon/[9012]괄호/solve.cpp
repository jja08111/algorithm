#include <iostream>
#include <string>
using namespace std;

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

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        string s;
        cin>>s;
        
        if(isVPS(s))
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }

    return 0;
}
