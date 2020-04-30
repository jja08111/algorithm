// skip이후 문자를 출력하는 함수를 만들고 
// 그 함수를 range번 반복한다.
// X,Y를 만났는데 gen이 0이 아니면 진화 해야한다.
// 진화시 길이가 어떻게 되는지 미리 구해놓음으로서 문제를 해결한다.

#include <iostream>
#include <string>
using namespace std;

const int MAX=1000000000+1;
const string EXPAND_X="X+YF";
const string EXPAND_Y="FX-Y";

int length[51];

// len[i]=2+2*len[i-1]인 점을 이용하여 i번 진화시의 문자열 길이를 구해놓는다.
void preCalc(void)
{
    length[0]=1;
    for(int i=1;i<=50;++i)
        length[i]=min(MAX,length[i-1]*2+2);
}

// 한글자씩 skip번째 다음 문자를 반환한다.
char expand(const string& dragonCurve, int gen, int skip)
{
    if(gen==0)
        return dragonCurve[skip];
    
    for(int i=0;i<dragonCurve.size();++i)
    {
        // 문자열이 확장되는 경우
        if(dragonCurve[i]=='X' || dragonCurve[i]=='Y')
        {
            // 확장되는 경우의 문자가 최종 진화되었을때만큼 skip하거나 진화
            if(skip>=length[gen])
                skip-=length[gen];
            else if(dragonCurve[i]=='X')
                return expand(EXPAND_X,gen-1,skip);
            else
                return expand(EXPAND_Y,gen-1,skip);
        }
        // 확장되진 않지만 건너 뛰어야 할 겨우
        else if(skip>0)
            --skip;
        // 답을 찾은 경우
        else
            return dragonCurve[i];
    }
    
    return '#';
}

int main(void)
{
    int testCase; 
    cin>>testCase;
    preCalc();
    
    while(testCase--)
    {
        int gen,skip,range; 
        cin>>gen>>skip>>range;

        for(int i=0;i<range;++i)
            cout<<expand("FX",gen,skip+i-1);
        cout<<endl;
    }

    return 0;
}
