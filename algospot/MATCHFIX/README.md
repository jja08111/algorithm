# 해결 
### 그래프 표현
처음에는 어떻게 그래프로 표현할 수 있을까 정말 많이 고민했다.  
교재는 경기에서 선수로 유량을 보낸다는 생각으로 그래프를 표현했다. 0번과 1번이 참여한 경기를 예로 들면 0번이 이기면 경기 정점에서 0번 선수 정점으로 유량 1을 보내는 것이다.  

이 아이디어로 소스에서 경기로, 경기에서 선수로, 선수에서 싱크로 간선을 연결하여 그래프를 만들 수 있다.  

### 용량 설정
이 다음에는 간선의 용량을 설정해야 한다. 소스에서 경기로는 각각 1만큼의 용량을, 경기에서 선수로 가는 간선도 각각 1씩 용량을 설정하면 된다.  

문제는 선수에서 싱크이다. 0번 선수가 단독 우승해야 하기 때문에 0번 선수의 승리 횟수는 다른 선수보다 같지 않고 커야 한다.  

```c++
// example data
1
// 참여 인원, 남은 경기 횟수
4 4
// 0,1,2,3번 선수의 각 승리 횟수
5 3 3 2
// 남은 경기 대진표
0 1 
1 2
2 3
1 3
```
위 예제 데이터를 보면 0번 선수가 5승으로 우승하려면 다른 선수들은 최대 4승까지 할 수 있다. 0번 선수는 이미 5승을 했기 때문에 추가적인 승을 가져갈 수 없다.
1번 선수와 2번 선수는 이미 3승을 했기 때문에 추가로 1승만 더 가져갈 수 있고 3번 선수는 2승을 했기 때문에 추가로 2승을 더 가져갈 수 있다.  

이와 같은 추가로 승리할 수 있는 횟수를 계산하여 용량에 설정하면 된다.  

### 구현 
위와 같이 유량 네트워크를 만들면 총 승리 횟수인 totalWins를 1씩 증가시켜 최대 유량이 남은 모든 경기와 같으면 되는 것이다.  
totalWins는 최대 wins[0] + maxAddWins(0번 선수가 추가로 할 수 있는 경기 수) 이다.  

totalWins를 증가 시킬때 계속해서 capacity를 계산하지 않고 변하는 부분인 선수에서 싱크로 가는 용량만 변경하여 최적화를 할 수 있다.  
또한 이미 얻은 flow를 초기화하여 다시 계산하지 않고 마지막에 계산했던 flow를 그대로 이용해도 된다.  

하지만 이때 주의할 점은 이전 총 유량의 합들이 누락될 수 있어 이들을 고려해야 한다.  

- 예를 들어 totalWins가 2승일 때 계산한 최대 유량이 1 이었는데 이 값이 m보다 작았다고 가정하자.  
totalWins를 3승으로 다시 계산하면 networkFlow 함수에서는 이전에 계산한 값인 1을 포함하여 계산하지 않을 수 있다.  
그렇기 때문에 이들을 고려해야 한다.  

구현 시 capacity와 flow의 인덱스를 아래와 같이 사용한 부분을 눈여겨 볼 필요가 있다.  
- 0 : 소스, 1 : 싱크 
- 2 ~ m-1 : 각 경기
- m ~ n-1 : 각 선수 
```c++
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX_V=2+200+20;
const int INF=987654321;

int V;
int n,m,totalFlow;
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
int wins[20], match[200][2];

int networkFlow(int source, int sink)
{
    int ret=0;
    while(true)
    {
        // 너비 우선 탐색으로 증가 경로를 찾는다.
        vector<int> parent(V,-1);
        queue<int> q;
        parent[source]=source;
        q.push(source);
        while(!q.empty() && parent[sink]==-1)
        {
            int here=q.front(); q.pop();
            for(int there=0;there<V;++there)
                if(parent[there]==-1 && capacity[here][there]-flow[here][there]>0)
                {
                    q.push(there);
                    parent[there]=here;
                }
        }
        // 증가 경로가 없으면 종료한다.
        if(parent[sink]==-1) break;
        // 증가 경로를 통해 유량을 얼마나 보낼지 결정한다.
        int amount=INF;
        for(int p=sink;p!=source;p=parent[p])
            amount=min(amount,capacity[parent[p]][p]-flow[parent[p]][p]);
        // 증가 경로를 통해 유량을 보낸다.
        for(int p=sink;p!=source;p=parent[p])
        {
            flow[parent[p]][p]+=amount;
            flow[p][parent[p]]-=amount;
        }
        ret+=amount;
    }
    // 이전에 계산한 Flow를 포함시켜 반환한다.
    return totalFlow+=ret;
}

// 0번 선수가 총 totalWins승으로 우승할 수 있는지 여부를 확인한다.
bool canWinWith(int totalWins)
{
    // 이미 totalWins승 이상 한 선수가 있으면 안된다. 
    if(*max_element(wins+1, wins+n)>=totalWins)
        return false;
    
    // 각 선수에서 싱크로, 가능한 최대 승수를 용량으로 하는 간선을 추가
    for(int i=0;i<n;++i)
    {
        int maxWin=(i==0 ? totalWins : totalWins-1);
        capacity[2+m+i][1]=maxWin-wins[i];
    }
    // 이때 모든 경기에 승자를 지정할 수 있는가?
    return networkFlow(0,1)==m;
}

// 우승할 수 있는 최소한의 총 승리 횟수 반환
int getMinTotalWins(const int maxAddWins)
{
    memset(flow,0,sizeof(flow));
    totalFlow=0;
    
    // 0번은 소스, 1번은 싱크로 설정
    V=2+m+n;
    memset(capacity,0,sizeof(capacity));
    for(int i=0;i<m;++i)
    {
        // 소스에서 각 경기로 가는 간선
        capacity[0][2+i]=1;
        // 각 경기에서 선수로 가는 간선
        for(int j=0;j<2;++j)
            capacity[2+i][2+m+match[i][j]]=1;
    }
    
    for(int i=0;i<=maxAddWins;++i)
        if(canWinWith(i+wins[0]))
            return i+wins[0];
    return -1;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>n>>m;
        
        for(int i=0;i<n;++i)
            cin>>wins[i];
        // 0번 선수가 추가로 이길 수 있는 최대 횟수
        int maxAddWins=0;
        for(int i=0;i<m;++i)
        {
            int a,b;
            cin>>a>>b;
            match[i][0]=a;
            match[i][1]=b;
            if(a==0 || b==0)
                ++maxAddWins;
        }
        
        cout<<getMinTotalWins(maxAddWins)<<endl;        
    }
    return 0;
}

```
