#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int INF=987654321;

vector<int> getPartialMatch(const string& s)
{
    int n=s.size();
    vector<int> pi(n,0);
    int begin=1, matched=0;
    while(begin+matched<n)
    {
        if(s[begin+matched]==s[matched])
        {
            matched++;
            pi[begin+matched-1]=matched;
        }
        else
        {
            if(matched==0)
                begin++;
            else
            {
                begin+=matched-pi[matched-1];
                matched=pi[matched-1];
            }
        }
    }
    return pi;
}

int minOverlap(const string& a, const string& b)
{
    int n=a.size(), m=b.size();
    vector<int> pi=getPartialMatch(b);
    int begin=0, matched=0, ret=INF;
    while(begin<n)
    {
        if(matched<m && a[begin+matched]==b[matched])
        {
            matched++;
            if(begin+matched==n)
            {
                string p=a.substr(0,n-matched);
                string q=b.substr(matched,m-matched);
                if(p==q)
                    return begin;
                begin++;
                matched=0;
            }
        }
        else
        {
            if(matched==0)
                begin++;
            else
            {
                begin+=matched-pi[matched-1];
                matched=pi[matched-1];
            }
        }
    }
    return -INF;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        string a,b;
        int n,ret=0;
        cin>>n;
        for(int i=0;i<n;++i)
        {
            if(i==0)
                cin>>a;
            
            if(i%2==0)
                cin>>b;
            else
                cin>>a;
            
            ret+=minOverlap(b,a);
        }
        cout<<ret<<endl;
    }
    
    return 0;
}
