# 해결 
입력된 수열을 부분마다 정렬을 모두 시도해 보며 수열로 그래프를 형성할 수 있다.  
하지만 최악의 경우 8!=20320개의 정점을 탐색해야 하는데, map에 접근하는 데 드는 시간이 크기 때문에 1000개의 테스트 케이스를 통과하긴 어렵다.  

### 모든 경우를 생성 
1. 숫자가 달라도 상대적인 크기가 같으면 같은 답을 출력한다.
예를 들어 배열 {2,42,100,80}과 {0,1,3,2}의 답은 같다. 

2. 이 문제의 상태 공간은 양방향 그래프이기 때문에, 시작 정점에서 목표 정점으로 가는 최단거리는 목표 정점에서 시작 정점으로 가는 최단거리와 같다.  

따라서 [0,1,2,...,7]의 모든 순열에 대해 필요한 뒤집기 연산의 수를 BFS를 이용하여 미리 구해 놓고 입력으로 들어오는 순열을 계산된 순열로 변환시켜 계산하면 쉽게 답을 구할 수 있다.  
```c++
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

const int MAX_N=8;

map<vector<int>,int> toSort;

void preCalc()
{
    vector<int> perm(MAX_N);
    for(int i=0;i<MAX_N;++i)
        perm[i]=i;
    
    queue<vector<int> > q;
    q.push(perm);
    toSort[perm]=0;
    while(!q.empty())
    {
        vector<int> here=q.front();
        q.pop();
        
        int cost=toSort[here];
        for(int i=0;i<MAX_N;++i)
            for(int j=i+2;j<=MAX_N;++j)
            {
                reverse(here.begin()+i,here.begin()+j);
                if(toSort.count(here)==0)
                {
                    q.push(here);
                    toSort[here]=cost+1;
                }
                reverse(here.begin()+i,here.begin()+j);
            }
    }
}

int solve(const vector<int>& seq)
{
    int n=seq.size();
    vector<int> compressed(MAX_N);
    for(int i=0;i<n;++i)
    {
        int smaller=0;
        for(int j=0;j<n;++j)
            if(seq[j]<seq[i])
                ++smaller;
        compressed[i]=smaller;
    }
    // 만약 수열의 길이가 8이 안되면 채운다.
    if(n!=MAX_N)
        for(int i=n;i<MAX_N;++i)
            compressed[i]=i;
    
    return toSort[compressed];
}

int main()
{
    int testCase;
    cin>>testCase;
    
    preCalc();
    
    while(testCase--)
    {
        int n;
        cin>>n;
        
        vector<int> seq(n);
        for(int i=0;i<n;++i)
            cin>>seq[i];
        
        cout<<solve(seq)<<endl;
    }

    return 0;
}
```
