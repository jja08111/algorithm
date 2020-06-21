#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> getPartialMatch(const string& s)
{
    int n=s.size();
    vector<int> pi(n,0);
    int begin=1, matched=0;
    while(begin+matched<n)
    {
        if(s[begin+matched]==s[matched])
        {
            ++matched;
            pi[begin+matched-1]=matched;
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
    return pi;
}

int maxOverlap(const string& a, const string& b)
{
    int n=a.size(), m=b.size();
    vector<int> pi=getPartialMatch(b);
    int begin=0, matched=0;
    while(begin<n)
    {
        if(matched<m && a[begin+matched]==b[matched])
        {
            ++matched;
            if(begin+matched==n)
                return matched;
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
    return 0;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        string s;
        cin>>s;
        string r=s;
        reverse(r.begin(),r.end());
        
        int ret=s.size()*2-maxOverlap(s,r);
        cout<<ret<<endl;
    }
    
    return 0;
}
