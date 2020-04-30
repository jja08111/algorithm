//bitmask를 이용하여 메모이제이션을 하였다.

#include <iostream>
#include <bitset>
using namespace std;

const int MAX=15;
const double INF=987654321.0;

int n;
double dist[MAX][MAX];
double cache[MAX][1<<MAX];

void init(void)
{
    cin>>n;
    
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            cin>>dist[i][j];
    
    // double형식은 memset을 사용할 수 없다.
    for (int i=0;i<MAX;i++)
        for (int j=0;j<(1<<MAX);j++)
            cache[i][j]=-1.0;
}

double shortestPath(int here, int visited)
{
    //기저사례 : 전부 방문한 경우
    if(visited==(1<<n)-1)
        return 0;
    
    double& ret=cache[here][visited];
    if(ret>=0)
        return ret;
    
    ret=INF;
    for(int next=0;next<n;++next)
    {
        //다음위치가 이미 방문한 경우
        if(visited & (1<<next))
            continue;
        double cand=dist[here][next]+shortestPath(next,visited+(1<<next));
        ret=min(ret,cand);
    }
    return ret;
}

int main(void)
{
    int testCase; 
    cin>>testCase;

    while(testCase--)
    {
        init();
        
        double ret=INF;
        
        //모든 위치에서 시작해 보며 최소값을 찾는다.
        for(int i=0;i<n;++i)
            ret=min(ret,shortestPath(i,1<<i));
        
        printf("%.10lf \n",ret);
    }

    return 0;
}
