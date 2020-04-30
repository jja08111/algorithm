#include <iostream>
using namespace std;

int seq[500];
int cache[501];
int n;

void init(void)
{
    cin>>n;
    
    for(int i=0;i<n;++i)
    {
        cin>>seq[i];
        cache[i]=-1;
    }
    //-1 index 부터 시작하니 끝에 하나더 초기화 한다
    cache[n]=-1;
}

int getMaxLen(int start)
{
    int& ret=cache[start+1];
    if(ret!=-1)
        return ret;
    
    //-1 index가 포함되어 있으니 최소 길이는 1이다.
    ret=1;
    for(int next=start+1;next<n;++next)
        if(start==-1 || seq[start]<seq[next])
            ret=max(ret,getMaxLen(next)+1);
    
    return ret;
}

int main(void)
{
    int testCase;
    
    cin>>testCase;
    
    while(testCase--)
    {
        init();
        
        //증가 부분 수열의 시작위치를 지정해 줘야 하니 -1 index부터 시작해 '결과-1' 을 반환한다.
        cout<<getMaxLen(-1)-1<<endl;
    }

    return 0;
}
