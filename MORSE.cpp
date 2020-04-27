#include <iostream>
#include <cstring>
using namespace std;
//int skip;
const int M=1000000000+100;
int bino[201][201];

//이항계수를 이용하여 [i][j] i에서 j개를 선택하는 조합 수를 계산한다.
void calcBino(void)
{
    memset(bino,0,sizeof(bino));
    
    for(int i=0;i<=200;++i)
    {
        bino[i][0]=bino[i][i]=1;
        for(int j=1;j<i;++j)
            bino[i][j]=min(M,bino[i-1][j-1]+bino[i-1][j]);
    }
}

/*
void generate(int n, int m, string s)
{
    if(skip<0) return;
    
    if(n==0 && m==0)
    {
        if(skip==0) cout<<s<<endl;
        --skip;
        return;
    }
    if(bino[n+m][n]<=skip)
    {
        skip-=bino[n+m][n];
        return;
    }
    if(n>0) generate(n-1,m,s+"-");
    if(m>0) generate(n,m-1,s+"o");
}*/

//모스부호중 맨 앞열의 문자를 만들어 나가며(skip<[n+m-1][n-1] 이면 맨앞이 '-'이다.)
//모스부호를 생성한다.
string kth(int n, int m, int skip)
{
    if(n==0) return string(m,'o');
    
    if(skip<bino[n+m-1][n-1])
        return "-"+kth(n-1,m,skip);
    return "o"+kth(n,m-1,skip-bino[n+m-1][n-1]);
}

int main(void)
{
    int testCase; cin>>testCase;
    
    while(testCase--)
    {
        int n,m,skip;
        
        cin>>n>>m>>skip;
        
        calcBino();
        //skip-1번 건너뛴다.
        cout<<kth(n,m,skip-1)<<endl;
    }

    return 0;
}
