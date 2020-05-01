#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MOD=1000000007;
//자릿수가 같기 떄문에 string을 이용하는 것이 훨씬 간편하다.
//digits : e의 자릿수들을 정렬한 것
string e,digits;
int n,m;
int cache[1<<14][20][2];

//완전탐색부터 시작한다.
//완전탐색시 중복되는 숫자는 다음과 같은 방법으로 제거할 수 있다.
// 1. 현재자리가 제일 첫번째이거나(i==0)
// 2. 바로 앞자리수와 현재자리수가 다르거나(digits[i-1]!=digits[i])
// 3. 같다면 이미 앞자리수가 사용되었거나(taken[i-1]==ture)
/*
void generate(string price, bool taken[15])
{
    if(price.size()==n)
    {
        if(price<e)
            cout<<price<<endl;
        return;
    }
    for(int i=0;i<n;++i)
    {
        if(!taken[i] && (i==0 || digits[i-1]!=digits[i] || taken[i-1]))
        {
            taken[i]=true;
            generate(price+digits[i],taken);
            taken[i]=false;
        }
    }
}
*/

// taken: 지금까지 사용한 자릿수들을 비트마스크로 표현
// mod: 핵심이라고 볼 수 있다. 수 전체를 넘기지 않고 m에 대한 나머지만을 넘긴다.
// less: 지금까지 만든 가격이 이미 e보다 작으면 1 아니면 0
int price(int index, int taken, int mod, int less)
{
    if(index==n)
        return (less && mod==0) ? 1 : 0;
    
    int& ret=cache[taken][mod][less];
    if(ret!=-1)
        return ret;
    
    ret=0;
    for(int next=0;next<n;++next)
    {
        if((taken&(1<<next))==0)
        {
            //과거 가격이 현재보다 커버리면 안된다.
            if(!less && e[index]<digits[next])
                continue;
            
            //같은 숫자를 중복되지 않게 선택하는 방법이다.
            if(next>0 && digits[next-1]==digits[next] && (taken & (1<<(next-1)))==0)
                continue;
            
            int nextTaken=taken|(1<<next);
            int nextMod=(mod*10+digits[next]-'0')%m;
            int nextLess=less||e[index]>digits[next];
            
            ret+=price(index+1,nextTaken,nextMod,nextLess);
            ret%=MOD;
        }
    }
    return ret;
}

int main(void)
{
    int testCase; cin>>testCase;
    
    while(testCase--)
    {
        cin>>e>>m;
        
        n=e.size();
        digits=e;
        sort(digits.begin(), digits.end());
        
        memset(cache,-1,sizeof(cache));
        
        cout<<price(0,0,0,0)<<endl;
    }

    return 0;
}
