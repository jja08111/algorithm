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
    if(indexA>=lenA || indexB>=lenB)
        return 0;
    
    ret=0;
    if(strA[indexA]==strB[indexB])
        return ret=LSC(indexA+1,indexB+1)+1;
    
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
