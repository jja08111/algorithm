# 해결 
이 문제를 해결하기 위해 모든 경우의 수를 만들어 d에 포함된 숫자인지 확인하는 방법을 떠올릴 수 있다.  
하지만 이 방법으로는 만들려는 최소 자연수 c가 엄청 클 수 있기 때문에 시간 내에 해결하기 어렵다.  

이 문제의 답인 조건을 만족하는 최소의 자연수 c를 n으로 나눈 나머지가 m이어야 한다.  
그렇다면 d에 포함된 숫자중 하나 x로 하나씩 뒤에 붙여 나간 수를 n(전체 아이들 수)만큼 나눈 나머지를 정점으로 표현해 보자.  
그러면 간선은 d에 포함된 숫자에서 하나를 고른 수 x가 된다.  
우리가 찾으려는 답은 만들어진 정점중 값이 욕심쟁이 아이들 수 m인 정점으로 가는 **최단경로**를 구하는 것이다.  
이 경로 중 사전순으로 빠른 값을 찾으면 된다.  

사전순으로 빠른 값을 찾는 방법은 너비 우선 탐색이 각 정점을 방문할 때마다 인접한 간선을 번호가 증가하는 순서로 검사하면 된다.

여기서 0번 정점에서 m번 정점까지 가는 최단 경로를 찾아 간선의 번로를 모아 만들어지는 값이 n+m 이상인 것을 확인해야 한다.  
방법은 n 미만인 정점과 n 이상인 경우의 정점을 구분하여 그래프를 만드는 것이다.  

실제 구현시 n보다 큰 정점을 n ~ 2n-1 로 표현한 것을 주의깊게 볼 필요가 있다.  
```c++
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

// here에서 간선 번호 edge를 따라갔을 때 나오는 정점
// mod 보다 큰 정점과 작은 정점을 구분해서 반환
int append(int here, int edge, int mod)
{
    int there=here*10+edge;
    if(there>=mod)
        return mod+there%mod;
    return there%mod;
}

string gifts(string digits, int n, int m)
{
    // 간선의 번호를 오름차순으로 정렬해 두면 사전순으로 가장 앞에 있는 경로를 찾을 수 있다.
    sort(digits.begin(),digits.end());
    
    // 흰색 정점 i는 0 ~ n-1, 회색 정점 i는 n ~ 2n-1로 표현한다.
    // parent[i]=BFS 스패닝 트리에서 정점 i의 부모
    // choice[i]=parent[i] 에서 i로 연결된 간선의 번호
    vector<int> parent(2*n, -1), choice(2*n,-1);
    queue<int> q;
    
    // 흰색 0번을 큐에 추가
    parent[0]=0;
    q.push(0);
    while(!q.empty())
    {
        int here=q.front();
        q.pop();
        for(int i=0;i<digits.size();++i)
        {
            // 간선 digits[i]-'0'을 따라가 본다.
            int there=append(here, digits[i]-'0', n);
            if(parent[there]==-1)
            {
                parent[there]=here;
                choice[there]=digits[i]-'0';
                q.push(there);
            }
        }
    }
    // 회색 m번에 도달하지 못했으면 실패!
    if(parent[n+m]==-1)
        return "IMPOSSIBLE";
    
    // 부모로 가는 연결을 따라가면서 조건을 만족하는 최소의 자연수 c를 찾는다.
    string ret;
    int here=n+m;
    while(parent[here]!=here)
    {
        ret+=char('0'+choice[here]);
        here=parent[here];
    }
    reverse(ret.begin(),ret.end());
    return ret;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        string digits;
        int n,m;
        cin>>digits>>n>>m;
        
        cout<<gifts(digits,n,m)<<endl;
    }

    return 0;
}

```


# 회고 
digits를 입력받을 때 int형으로 받으면 0이 무시되어 틀린 값을 반환한다.
