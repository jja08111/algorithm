#include <iostream>
#include <cstring>
using namespace std;

const int MOD=10*1000*1000;
int cache[101][101];

int poly(int n, int parts)
{
    if(n==0)
        return 1;
    
    int& ret=cache[n][parts];
    if(ret!=-1)
        return ret;
    
    ret=0;
    for(int nextParts=1;nextParts<=n;++nextParts)
        ret=(ret+poly(n-nextParts,nextParts)*(parts+nextParts-1))%MOD;
    
    return ret;
}

int main(void)
{
    int testCase;
    
    cin>>testCase;
    
    while(testCase--)
    {
        int n; cin>>n;
        int ret=0;
        
        memset(cache,-1,sizeof(cache));
        
        for(int i=1;i<=n;++i)
            ret=(ret+poly(n-i,i))%MOD;
            
        cout<<ret<<endl;
    }
    
    return 0;
}

/*
종만북 코드
int poly(int n, int first)
{
    if(n==first)
        return 1;
    
    int& ret=cache[n][first];
    if(ret!=-1)
        return ret;
    
    ret=0;
    for(int second=1;second<=n-first;++second)
    {
        //add라는 변수를 만들어서 직관.
        int add=second+first-1;
        add*=poly(n-first,second);
        add%=MOD;
        ret+=add;
        ret%=MOD;
    }
    return ret;
}

*/
