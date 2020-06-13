#include <iostream>
#include <vector>
using namespace std;

const int INF=987654321;

int n;
int ability[20][20];
int ret=INF;

void getMinDiff(int team)
{
    int startAbility=0, linkAbility=0;
    
    for(int a=0;a<n;++a)
        for(int b=a+1;b<n;++b)
        {
            if(((1<<a)&team) && ((1<<b)&team))
                startAbility+=(ability[a][b]+ability[b][a]);
            else if(!((1<<a)&team) && !((1<<b)&team))
                linkAbility+=(ability[a][b]+ability[b][a]);
        }
    
    ret=min(ret,abs(startAbility-linkAbility));
}

void solve(int visited)
{
    if(__builtin_popcount(visited)==n/2)
        getMinDiff(visited);

    int here=0;
    for(int i=0;i<n;++i)
        if(visited&(1<<i))
            here=i;
    
    for(int i=here+1;i<n;++i)
    {
        int next=(1<<i);
        if(!(visited&next))
            solve(visited|next);
    }
}

int main()
{
    cin>>n;
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            cin>>ability[i][j];
    
    solve(1);
    cout<<ret;
    
    return 0;
}
