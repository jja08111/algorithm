#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int INF=987654321;
const int MAXN=12;

int subjectNum, need, semesterNum, attendLimit;
//필요한 선수과목, 학기당 개설되는 과목정보를 비트로 표현
vector<int> prerequisite, classes;
int cache[1<<MAXN][10];

void readVector(vector<int>& v, int n)
{
    for(int i=0;i<n;++i)
    {
        int n;
        cin>>n;
        v.push_back(0);
        for(int j=0;j<n;++j)
        {
            int tmp;
            cin>>tmp;
            v[i]|=(1<<tmp);
        }
    }
}

void init()
{
    prerequisite.clear();
    classes.clear();
    memset(cache,-1,sizeof(cache));
    
    cin>>subjectNum>>need>>semesterNum>>attendLimit;
    readVector(prerequisite,subjectNum);
    readVector(classes,semesterNum);
}

int solve(int taken, int semester)
{
    //기저 사례: 학기를 초과한 경우
    if(semester>semesterNum)
        return INF;
    //기저 사례: 과목을 전부 수강한 경우
    if(taken==((1<<subjectNum)-1))
        return 0;
    
    //메모이제이션을 이용
    int& ret=cache[taken][semester];
    if(ret!=-1)
        return ret;
    
    //현재 학기에서 들을 수 있는 강의 중 아직 듣지 않은 강의를 찾음
    int canTake=(classes[semester] & ~taken);
    for(int i=0;i<subjectNum;++i)
        //이번 학기에 개설되고 선수과목이 해결 안된 경우
        if((classes[semester]&(1<<i)) && (taken&prerequisite[i])!=prerequisite[i])
            canTake &= ~(1<<i);
    
    ret=INF;
    for(int subset=canTake;subset;subset=((subset-1)&canTake))
        if(__builtin_popcount(subset)<=attendLimit)
            ret=min(ret,solve(taken|subset,semester+1)+1);
    //이번 학기에 아무 것도 듣지 않을 경우
    ret=min(ret,solve(taken,semester+1));
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
