//재쉬함수로 구현했다.
//보면 알다시피 cache의 index가 100000밖에 되지 않아 모든 값을 표현할 수 없다.
//그리고 속도도 느려서 문제를 풀 수 없다.
#include <iostream>
#include <cstring>
using namespace std;

int n, k, favorite;
int len[50];
double adj[50][50];
double cache[100000][50];

void init(void)
{
    cin>>n>>k>>favorite;
    for(int i=0;i<n;++i)
        cin>>len[i];
    for(int y=0;y<n;++y)
        for(int x=0;x<n;++x)
            cin>>adj[y][x];
    memset(cache,-1,sizeof(cache));
}

double getProb(int passedTime, int here)
{
    if(passedTime==0 && here==0)
        return 1;
    
    double &ret=cache[passedTime][here];
    if(ret>-0.5)
        return ret;
    
    ret=0;
    for(int prev=0;prev<n;++prev)
        if(passedTime>=len[prev])
            ret+=getProb(passedTime-len[prev],prev)*adj[prev][here];
    
    return ret;
}

int main(void)
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        init();
        
        for(int i=0;i<favorite;++i)
        {
            int song;
            cin>>song;
            
            double ret=0;
            //노래가 시작할때의 확률이 아닌 재생되고 있는지에 대한 확률이니 k-len[song]+1만큼 앞까지 합한다.
            for(int j=0;j<len[song];++j)
                ret+=getProb(k-j,song);
            printf("%.10lf ",ret);
        }
        cout<<endl;
    }

    return 0;
}
