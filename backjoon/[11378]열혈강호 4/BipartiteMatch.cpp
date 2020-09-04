#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAX=1001;
const int INF=987654321;

int n,m,k;
vector<int> adj[MAX];
// b와 매칭된 a정점 목록
vector<int> bMatch;
vector<bool> visited;

void makeGraph()
{
    cin>>n>>m>>k;
    for(int i=0;i<MAX;++i)
        adj[i].clear();
    for(int person=0;person<n;++person)
    {
        int canDoNum;
        cin>>canDoNum;
        for(int j=0;j<canDoNum;++j)
        {
            int todo;
            cin>>todo;
            --todo;
            adj[person].push_back(todo);
        }
    }
}

bool dfs(int a)
{
    if(visited[a])
        return false;
    visited[a]=true;
    for(int i=0;i<adj[a].size();++i)
    {
        int b=adj[a][i];
        // b가 이미 매칭되어 있다면 bMatch[b]에서부터 시작해 증가 경로를 찾는다.(역방향으로 유량을 보내는 것과 비슷함)
        if(bMatch[b]==-1 || dfs(bMatch[b]))
        {
            bMatch[b]=a;
            return true;
        }
    }
    return false;
}

int getMaxNum()
{
    bMatch=vector<int>(m,-1);
    int size=0;
    for(int start=0;start<n;++start)
    {
        visited=vector<bool>(n,false);
        if(dfs(start))
            ++size;
    }
    for(int start=0;start<n;++start)
    {
        while(k)
        {
            visited=vector<bool>(n,false);
            // 해당 직원으로는 추가적인 일을 부여할 수 없는 경우
            if(!dfs(start))
                break;
            // 일을 부여하고 벌점을 삭감
            ++size;
            --k;
        }
    }
    return size;
}

int main()
{
    makeGraph();
    
    cout<<getMaxNum()<<endl;
    return 0;
}
