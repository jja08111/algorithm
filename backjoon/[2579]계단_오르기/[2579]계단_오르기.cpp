#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int NAGINF=-987654321;
int n, stair[301];
int cache[301][3];

//현재 계단 위치와 얼마나 연속해서 걸어왔는지를 통해 최대스코어합을 반환한다.
int getMaxScore(int here, int consecutiveStep)
{
    //계단을 3개 연속으로 밟거나 범위를 벗어난 경우
    if(consecutiveStep>=3 || here>n)
        return NAGINF;
    
    //마지막 계단에 오른 경우
    if(here==n)
        return stair[here];
    
    int& ret=cache[here][consecutiveStep];
    if(ret!=-1)
        return ret;
    
    ret=stair[here];
    ret+=max(getMaxScore(here+1,consecutiveStep+1),getMaxScore(here+2,1));
    
    return ret;
}

int main(void)
{
    cin>>n;
    
    stair[0]=0;
    for(int i=1;i<=n;++i)
        cin>>stair[i];
    
    memset(cache,-1,sizeof(cache));
    
    cout<<getMaxScore(0,0)<<endl;

    return 0;
}
