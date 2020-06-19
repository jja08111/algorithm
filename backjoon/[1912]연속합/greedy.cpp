#include <iostream>
using namespace std;

const int NAG_INF=-987654321;
const int MAX=100000;

int n,seq[MAX];
int answer=NAG_INF;

int solve(int start)
{
    if(start==n)
        return 0;
    
    //현재 숫자를 포함한다.
    int ret=seq[start];
    //다음 숫자부터 시작하는 수열들 중 최대합을 찾는다.
    int next=solve(start+1);
    //다음 수열이 음수인 경우 포함하지 않는다.
    ret+=max(0,next);
    
    //최대값을 전역변수에 저장하여 따로 반복문을 만들지 않는다.
    answer=max(answer,ret);
    
    return ret;
}

int main()
{
    cin>>n;
    for(int i=0;i<n;++i)
        cin>>seq[i];
    
    solve(0);
    cout<<answer;
    return 0;
}
