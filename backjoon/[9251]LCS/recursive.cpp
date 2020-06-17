#include <iostream>
#include <cstring>
using namespace std;

const int MAX=1002;

string strA,strB;
int lenA,lenB;
int cache[MAX][MAX];

int LSC(int indexA, int indexB)
{
    int& ret=cache[indexA][indexB];
    if(ret!=-1)
        return ret;
    
    ret=0;
    int nextB;
    for(nextB=indexB;nextB<lenB;++nextB)
        if(strA[indexA]==strB[nextB])
            ret=max(ret,LSC(indexA+1,nextB+1)+1);
    
    if(indexA<lenA && nextB==lenB)
        ret=max(ret,LSC(indexA+1,indexB));
    
    return ret;
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
