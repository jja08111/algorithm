# 해결 
이 문제는 [[11280]2-SAT - 3](https://github.com/jja08111/algorithm/tree/master/backjoon/%5B11280%5D2-SAT%20-%203)문제와 유사하며 해를 추가로 구하면 되는 문제이다.  

해를 구하기 위해서는 이전 문제에서 설명했던 것처럼 참 정점에서 거짓 정점으로 가는 간선이 존재하면 안된다.  
그렇다면 들어오는 간선이 없는 정점을 거짓으로 분류하는 것으로 시작하여 해결할 수 있다.  
scc번호가 위상정렬의 역순으로 부여된다는 점을 아는가? 타잔의 알고리즘은 DFS과정을 통해 scc별로 분리를 하기 때문에 역순으로 번호가 부여된다.  

이점을 이용하여 역으로 재정렬 한 뒤, 제일 첫 정점을 거짓으로 분류하고 대응되는 정점은 참으로 분류한다.(실제 구현시에는 대응되는 점은 무시한다.)  
그 후 이미 참으로 분류된 정점은 무시하며 반복하면 해를 구할 수 있다.  

구현 시 첫 정점을 2로 나누어 실제 값의 변수에 접근한다. 이 변수를 거짓이면 참, 참이면 거짓으로 분류해 나가며 변수가 이미 분류된 경우는 건너뛰어 해결한다.  
```c++
vector<int> solve2SAT()
{
    int n=adj.size();
    makeSCCs();
    // 해를 구할 수 없는 경우 
    for(int i=0;i<n;i+=2)
        if(sccId[i]==sccId[i+1])
            return vector<int>();
    
    // scc가 위상정렬의 역순으로 번호가 배정된 점을 이용한다.
    vector<pair<int,int> > order;
    for(int i=0;i<n;++i)
        order.push_back(make_pair(-sccId[i],i));
    sort(order.begin(), order.end());
    
    vector<int> value(n,-1);
    for(int i=0;i<n;++i)
    {
        int vertex=order[i].second;
        int variable=vertex/2, isTrue=vertex%2==0;
        if(value[variable]!=-1)
            continue;
        value[variable]=!isTrue;
    }
    return value;
}
```
