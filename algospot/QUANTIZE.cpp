//복습하며 놓친 부분을 주석으로 표시했다.
//
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int INF=987654321;

int n,seq[101];
int pSum[101],pSqSum[101];
int cache[101][11];

void preCalc(void)
{
    sort(seq,seq+n);
    
    pSum[0]=seq[0];
    pSqSum[0]=seq[0]*seq[0];
    
    for(int i=1;i<n;++i)
    {
        pSum[i]=pSum[i-1]+seq[i];
        pSqSum[i]=pSqSum[i-1]+seq[i]*seq[i];
    }
}

void init(int& combi)
{
    cin>>n>>combi;
    
    for(int i=0;i<n;++i)
    {
        scanf("%d",&seq[i]);
        memset(cache[i],-1,sizeof(int)*11);
    }
    
    preCalc();
}

int minError(int lo, int hi)
{
    //lo~hi 까지의 범위이기 때문데 lo-1 인덱스의 값을 빼줘야 한다.
    int sum=pSum[hi]-(lo==0 ? 0 : pSum[lo-1]);
    int sqSum=pSqSum[hi]-(lo==0 ? 0 : pSqSum[lo-1]);
    
    //실수로 변환 후 계산 해야한다.
    int m=(int)(0.5+(double)sum/(hi-lo+1));
    
    return sqSum-2*sum*m+m*m*(hi-lo+1);
}

int quantize(int from, int parts)
{
    if(from==n)
        return 0;
    if(parts==0)
        return INF;
    
    int& ret=cache[from][parts];
    if(ret!=-1)
        return ret;
    
    ret=INF;
    //기저사례가 from==n이니 from+partSize<=n 이어야 한다.
    for(int partSize=1;from+partSize<=n;++partSize)
        ret=min(ret,minError(from,from+partSize-1)+quantize(from+partSize,parts-1));
    
    return ret;
}

int main(void)
{
    int testCase;
    
    cin>>testCase;
    
    while(testCase--)
    {
        int combi;
        
        init(combi);
        
        cout<<quantize(0,combi)<<endl;
    }
}
