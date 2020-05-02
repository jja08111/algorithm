#include <iostream>
using namespace std;

int len, seq[1001], cache[1001];

int LIS(int start)
{
    int& ret=cache[start+1];
    if(ret!=-1)
        return ret;
    
    //-1부터 시작하니 길이는 최소 1이다.
    ret=1;
    for(int next=start+1;next<len;++next)
        if(start==-1 || seq[start]<seq[next])
            ret=max(ret,LIS(next)+1);
    
    return ret;
}

int main(void)
{
    cin>>len;
    
    for(int i=0;i<len;++i)
    {
        cin>>seq[i];
        cache[i]=-1;
    }
    //-1부터 시작하니 끝에 하나 더 초기화 해준다.
    cache[len]=-1;
    
    //-1부터 시작함으로써 반복문을 사용하지 않아도 된다.
    cout<<LIS(-1)-1;
    
    return 0;
}
