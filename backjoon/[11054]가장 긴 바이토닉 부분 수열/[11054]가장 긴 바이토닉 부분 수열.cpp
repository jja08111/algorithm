#include <iostream>
using namespace std;

int len, seq[1001], leftCache[1001], rightCache[1002];

int leftLIS(int start)
{
    int& ret=leftCache[start+1];
    if(ret!=-1)
        return ret;
    
    ret=1;
    for(int next=start+1;next<len;++next)
        if(start==-1 || seq[start]>seq[next])
            ret=max(ret,leftLIS(next)+1);
    
    return ret;
}

int rightLIS(int start)
{
    int& ret=rightCache[start+1];
    if(ret!=-1)
        return ret;
    
    ret=1;
    for(int next=start-1;next>=0;--next)
        if(start==len || seq[next]<seq[start])
            ret=max(ret,rightLIS(next)+1);
    
    return ret;
}

int main(void)
{
    cin>>len;
    
    for(int i=0;i<len;++i)
    {
        cin>>seq[i];
        leftCache[i]=-1;
        rightCache[i]=-1;
    }
    leftCache[len]=rightCache[len]=rightCache[len+1]=-1;
    
    leftLIS(-1);
    rightLIS(len);

    int ret=0;
    for(int i=1;i<=len;++i)
    {
        int sum;
        sum=leftCache[i]+rightCache[i];
        ret=max(ret,sum);
    }
    cout<<ret-1;
    
    return 0;
}
