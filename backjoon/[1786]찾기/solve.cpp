#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getPartialMatch(const string& s)
{
    int n=s.size();
    vector<int> ret(n,0);
    int begin=1, matched=0;
    while(begin+matched<n)
    {
        if(s[begin+matched]==s[matched])
        {
            ++matched;
            ret[begin+matched-1]=matched;
        }
        else
        {
            if(matched==0)
                ++begin;
            else
            {
                begin+=matched-ret[matched-1];
                matched=ret[matched-1];
            }
        }
    }
    return ret;
}

vector<int> KMPsearch(const string& T, const string& P)
{
    int n=T.size(), m=P.size();
    vector<int> ret;
    vector<int> pi=getPartialMatch(P);
    int begin=0, matched=0;
    while(begin<=n-m)
    {
        if(matched<m && T[begin+matched]==P[matched])
        {
            ++matched;
            if(m==matched)
                ret.push_back(begin+1);
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
    return ret;
}

int main()
{
    string T,P;
    getline(cin,T);
    getline(cin,P);
    
    vector<int> ret=KMPsearch(T,P);
    int n=ret.size();
    cout<<n<<endl;
    for(int i=0;i<n;++i)
        printf("%d ",ret[i]);

    return 0;
}
