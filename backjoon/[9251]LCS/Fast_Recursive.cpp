#include <iostream>
#include <cstring>
using namespace std;

const int MAX=1001;

string strA,strB;
int lenA,lenB;
int cache[MAX][MAX];

int LSC(int indexA, int indexB)
{
    int& ret=cache[indexA][indexB];
    if(ret!=-1)
        return ret;
    //범위를 벗어나면 종료한다.
    if(indexA>=lenA || indexB>=lenB)
        return 0;
    
    ret=0;
    //문자가 일치하는 경우
    if(strA[indexA]==strB[indexB])
        return ret=LSC(indexA+1,indexB+1)+1;
    
    //문자가 일치하지 않는 경우
    return ret=max(LSC(indexA+1,indexB),LSC(indexA,indexB+1));
}

int main()
{
    cin>>strA>>strB;
    lenA=strA.size();
    lenB=strB.size();
    memset(cache,-1,sizeof(cache));
    
    cout<<LSC(0,0);

    return 0;
}
