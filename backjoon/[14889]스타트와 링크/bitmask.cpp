#include <iostream>
using namespace std;

const int INF=987654321;

int n,ability[20][20];
int ret=INF;

void getMinDiff(int team)
{
    int startAbility=0, linkAbility=0;
    
    for(int a=0;a<n;++a)
        for(int b=a+1;b<n;++b)
        {
            // a선수와 b선수가 start팀에 속하는 경우
            if(((1<<a)&team) && ((1<<b)&team))
                startAbility+=(ability[a][b]+ability[b][a]);
            // a선수와 b선수가 link팀에 속하는 경우
            else if(!((1<<a)&team) && !((1<<b)&team))
                linkAbility+=(ability[a][b]+ability[b][a]);
        }
    
    ret=min(ret,abs(startAbility-linkAbility));
}

// 비트 마스크를 이용
void solve(int selected)
{
    if(ret==0) return;
    // 선수 선택을 완료한 경우
    if(__builtin_popcount(selected)==n/2)
    {
        getMinDiff(selected);
        return;
    }
    
    // 중복을 막기 위해 가장 번호가 큰 선택된 선수를 찾는다.
    int here=0;
    for(int i=n-1;i>=0;--i)
        if(selected&(1<<i))
        {
            here=i;
            break;
        }
    
    // dfs
    for(int i=here+1;i<n;++i)
    {
        int next=(1<<i);
        if(!(selected&next))
            solve(selected|next);
    }
}

int main()
{
    cin>>n;
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            cin>>ability[i][j];
    
    // 0번 선수가 있는 팀과 없는 팀으로 나눠서 해결
    solve(1);
    cout<<ret;
    
    return 0;
}
