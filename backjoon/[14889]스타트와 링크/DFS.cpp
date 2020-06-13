#include <iostream>
using namespace std;

const int INF=987654321;

bool isSelected[20];
int n,ability[20][20];
int ret=INF;

void getMinDiff()
{
    int startAbility=0, linkAbility=0;
    
    for(int a=0;a<n;++a)
        for(int b=a+1;b<n;++b)
        {
            // a선수와 b선수가 start팀에 속하는 경우
            if(isSelected[a] && isSelected[b])
                startAbility+=(ability[a][b]+ability[b][a]);
            // a선수와 b선수가 link팀에 속하는 경우
            else if(!isSelected[a] && !isSelected[b])
                linkAbility+=(ability[a][b]+ability[b][a]);
        }
    
    ret=min(ret,abs(startAbility-linkAbility));
}

void solve(int here, int count)
{
    if(ret==0) return;
    // 선수 선택을 완료한 경우
    if(count==n/2)
    {
        getMinDiff();
        return;
    }
    
    // dfs
    for(int there=here+1;there<n;++there)
        if(!isSelected[there])
        {
            isSelected[there]=true;
            solve(there,count+1);
            isSelected[there]=false;
        }
}

int main()
{
    cin>>n;
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            cin>>ability[i][j];
    
    // 0번 선수가 있는 팀과 없는 팀으로 나눠서 해결
    isSelected[0]=true;
    
    solve(0,1);
    cout<<ret;
    
    return 0;
}
