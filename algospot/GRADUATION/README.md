# 해결 
이 문제는 동적 계획법과 비트마스크를 이용하여 해결하는 문제이다.  
선수과목의 집합과 학기당 열리는 강의들의 집합을 비트마스크로 표현해 계산을 빠르고 간단하게 할 수 있다.  

재귀적으로 구현하기 위해서는 현재까지 들은 강의가 무엇이고 현재 몇째 학기인지를 알면 구현할 수 있다.  
기저 사례는 학기를 초과한 경우 혹은 과목을 전부 수강한 경우로 둘 수 있다.  
메모이제이션을 적용할 수 있으니 적용한다.  

그 다음 현재 학기에서 들을 수 있는 강의중 듣지 않은 강의를 골라내고 여기서 선수과목이 해결된 강의만 다시 골라내어 들을 수 있는 강의를 찾을 수 있다.  
그리고 모든 집합을 탐색아여 최소의 값이 나오는 경우를 찾는다.  
여기서 중요한 것은 이번 학기에 아무 것도 듣지 않는 경우를 고려해야 한다는 점이다.
```c++
int subjectNum, need, semesterNum, attendLimit;
//필요한 선수과목, 학기당 개설되는 과목정보를 비트로 표현
vector<int> prerequisite, classes;
int cache[1<<12][10];

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
```


# 회고 
- 처음에는 문제를 보고 비트 마스크를 이용하여 집합인 부분을 간단하게 해결해야겠다는 생각만 했다.  
그래서 메모이제이션을 한다는 것을 잊고 있었다.  
- 현재 학기에 들을 수 있는 강의를 찾을 때 이미 들은 강의를 같이 제거했어야 했다.  
그리고 chechPre()를 구현하기 보다는 비트연산을 이용했어야 했다.  
```c++
//int auditable=0;
//for(int i=0;i<subjectNum;++i)
//    이번학기에 개설되고 선수과목이 해결된 경우
//    if((semester[count]&(1<<i)) && checkPre(taken,i))
//        auditable|=(1<<i);

//현재 학기에서 들을 수 있는 강의 중 아직 듣지 않은 강의를 찾음
int canTake=(classes[semester] & ~taken);
for(int i=0;i<subjectNum;++i)
    //이번 학기에 개설되고 선수과목이 해결 안된 경우
    if((classes[semester]&(1<<i)) && (taken&prerequisite[i])!=prerequisite[i])
        canTake &= ~(1<<i);
```
