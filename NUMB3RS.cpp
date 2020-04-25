#include <iostream>
#include <cstring>
using namespace std;

double cache[50][100];
int deg[50];
bool adj[50][50];
int n,d,prison;

void init(void)
{
    cin>>n>>d>>prison;
    
    memset(deg,0,sizeof(deg));
    
    for(int i=0;i<n;++i)
    {
        memset(cache[i],-1,sizeof(double)*100);
        for(int j=0;j<n;++j)
        {
            scanf("%d",&adj[i][j]);
            if(adj[i][j])
                ++deg[i];
        }
    }
}

//탐색의 핵심은 탐색 방햑을 prison에서 경로의 끝이 아닌 
//경로의 끝부터 prison으로 가는 방향을 탐색해
//수행시간을 단축할 수 있다.
double solve(int here, int days)
{
    if(days==0)
        return (here==prison ? 1 : 0);
    
    double &ret=cache[here][days];
    if(ret>-0.5)
        return ret;
    
    ret=0;
    for(int there=0;there<n;++there)
        if(adj[here][there])
            ret+=solve(there,days-1)/deg[there];
    
    return ret;
}

int main(void)
{
    int testCase;
    
    cin>>testCase;
    
    while(testCase--)
    {
        init();
        
        int calcNum; cin>>calcNum;
        
        for(int i=0;i<calcNum;++i)
        {
            int tmp; cin>>tmp;
            printf("%.10lf ",solve(tmp,d));
        }
        cout<<endl;
    }
    
    return 0;
}
