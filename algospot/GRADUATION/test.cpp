#include <iostream>
#include <vector>
using namespace std;

const int INF=987654321;

int subjectNum, need, semesterNum, attendLimit;
// 선수과목, 학기당 과목정보를 비트로 표현
vector<int> prerequisite, semester;

void readData(vector<int>& data, int n)
{
    for(int i=0;i<n;++i)
    {
        int n;
        cin>>n;
        data.push_back(0);
        for(int j=0;j<n;++j)
        {
            int tmp;
            cin>>tmp;
            data[i]|=(1<<tmp);
        }
    }
}

void init()
{
    prerequisite.clear();
    semester.clear();
    
    cin>>subjectNum>>need>>semesterNum>>attendLimit;
    readData(prerequisite,subjectNum);
    readData(semester,semesterNum);
}

bool checkPre(int taken, int subject)
{
    if(prerequisite[subject]==0)
        return true;
    
    int mask=prerequisite[subject];
    while(mask)
    {
        int bit=mask&-mask;
        if(!(bit&taken))
            return false;
        mask^=bit;
    }
    return true;
}

int solve(int taken, int count)
{
    if(count>semesterNum)
        return INF;
    int MASK=(1<<subjectNum)-1;
    if(taken==MASK)
        return count-1;
    
    int auditable=0;
    for(int i=0;i<subjectNum;++i)
        //이번학기에 개설되고 선수과목이 해결된 경우
        if((semester[count]&(1<<i)) && checkPre(taken,i))
            auditable|=(1<<i);
    
    int ret=INF;
    for(int subset=auditable;subset;subset=((subset-1)&auditable))
        if(__builtin_popcount(subset)<=attendLimit)
            ret=min(ret,solve(taken|subset,count+1));

    return ret;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        init();
        
        int ret=solve(0,0);
        if(ret==INF)
            cout<<"IMPOSSIBLE"<<endl;
        else
            cout<<ret<<endl;
    }
    return 0;
}
