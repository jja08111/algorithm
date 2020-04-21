// WARNING This code is incomplete

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF=987654321;

string pi;
int cache[10001];
int len;

int classify(int start, int end)
{
    for(int idx=start;idx<end-1;++idx)
    {    
        if(pi[idx]==pi[idx+1])
            if(idx==end-2)
                return 1;
        else
            break;
    }
    
    int diff=pi[start+1]-pi[start];
    int level=(abs(diff)>1) ? 5 : 2;
    //int delta=diff/abs(diff);
    
    for(int idx=start;idx<end-1;++idx)
        if(pi[idx]!=pi[idx+1]+diff)
        {
            if(pi[idx]==pi[idx+1]+(diff*-1))
                level=4;
            else
                return 10;
        }
    
    return level;
}

int getMinLevel(int start)
{
    if(start==len)
        return 0;
    
    int& ret=cache[start];
    if(ret!=-1)
        return ret;
    
    ret=INF;
    for(int next=start+3;next<=start+5;++next)
        if(next<=len)
            ret=min(ret, classify(start, next)+getMinLevel(next));
    
    return ret;
}

int main(void)
{
    int testCase;
    
    cin>>testCase;
    
    while(testCase--)
    {
        cin>>pi;
        
        memset(cache,-1,sizeof(cache));
        
        len=pi.length();
        
        cout<<getMinLevel(0)<<endl;
    }
    
    return 0;
}
