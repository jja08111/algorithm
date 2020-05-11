/* 완성되지 않은 
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int n, k, favorite;
int len[50];
double adj[50][50];

void init(void)
{
    cin>>n>>k>>favorite;
    for(int i=0;i<n;++i)
        cin>>len[i];
    for(int y=0;y<n;++y)
        for(int x=0;x<n;++x)
            cin>>adj[y][x];
}

vector<double> getProb(void)
{
    //sliding window기법 사용
    double c[5][50];
    memset(c,0,sizeof(c));
    c[0][0];
    for(int passedTime=1;passedTime<=k;++passedTime)
        for(int song=0;song<n;++song)
        {
            double& prob=c[passedTime%5][song];
            prob=0;
            for(int last=0;last<n;++last)
                prob+=c[(passedTime-len[last]+5)%5][last]*adj[last][song];
        }
    
    vector<double> ret(n);
    for(int song=0;song<n;++song)
        for(int start=k-len[song]+1;start<=k;++start)
            ret[song]+=c[start%5][song];
    
    return ret;
}

int main(void)
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        init();
        
        vector<double> ret=getProb();
        for(int i=0;i<favorite;++i)
        {
            int song;
            cin>>song;
            printf("%.10lf ",ret[song]);
        }
        cout<<endl;
    }

    return 0;
}
*/
