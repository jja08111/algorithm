#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAX=1001;
const int INF=987654321;

int n,m,k;
vector<int> adj[MAX];
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
            if(!dfs(start))
                break;
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
