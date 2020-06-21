#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> getPartialMatch(const string& s)
{
    int n=s.size();
    vector<int> pi(n,0);
    int begin=1, matched=0;
    while(begin+matched<n)
    {
        if(s[matched]==s[begin+matched])
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

vector<int> getPrefixSuffix(const string& s)
{
    vector<int> ret, pi=getPartialMatch(s);
    int k=s.size();
    while(k>0)
    {
        ret.push_back(k);
        k=pi[k-1];
    }
    return ret;
}

int main()
{
    string father,mother;
    cin>>father>>mother;
    string s=father+mother;
    
    vector<int> ret=getPrefixSuffix(s);
    for(int i=ret.size()-1;i>=0;--i)
        cout<<ret[i]<<" ";
    
    return 0;
}
