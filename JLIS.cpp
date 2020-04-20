//처음에는 두개의 수열을 각각 따로 처리하려 했으나 방법이 나오지 않아 책을 보았다.
//내가 부족한 부분은 문제를 어떤식으로 해결해 나가는지 정확히 이해하지 못한 것이다.
//양쪽 수열중 번갈아가며 모두를 찾아 나가야 하는데 따로하려고 했던 것이 문제이다.
////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//입력이 모든 32bit 정수이니 최소값을 다음과 같이한다.
const long long NEGINF=numeric_limits<long long>::min();
int A[100],B[100];
int cache[101][101];
int an,bn;
    
void init(void)
{
    cin>>an>>bn;
    
    for(int i=0;i<101;++i)
        memset(cache[i],-1,sizeof(int)*101);
    
    for(int i=0;i<an;++i)
        cin>>A[i];
    for(int i=0;i<bn;++i)
        cin>>B[i];    
}

//indexA, indexB를 포함한 수열중 가장 긴 증가부분 수열의 길이 반환
int getMaxLen(int indexA, int indexB)
{
    int& ret=cache[indexA+1][indexB+1];
    
    if(ret!=-1)
        return ret;
    
    ret=2;
    
    //A[indexA]와 B[indexB] 중 더 큰값과 나머지 수열을 비교
    long long a=(indexA==-1) ? NEGINF : A[indexA];
    long long b=(indexB==-1) ? NEGINF : B[indexB];
    long long maxElement=max(a,b);
    
    //A와 B수열 둘다 재귀하며 가장 큰 값을 찾음
    for(int nextA=indexA+1;nextA<an;++nextA)
        if(maxElement<A[nextA])
            ret=max(ret,getMaxLen(nextA,indexB)+1);
    for(int nextB=indexB+1;nextB<bn;++nextB)
        if(maxElement<B[nextB])
            ret=max(ret,getMaxLen(indexA,nextB)+1);
    
    return ret;
}

int main(void)
{
    int testCase;
    
    cin>>testCase;
    
    while(testCase--)
    {
        init();
        
        cout<<getMaxLen(-1,-1)-2<<endl;
    }

    return 0;
}
