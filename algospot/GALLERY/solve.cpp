#include <iostream>
#include <vector>
using namespace std;

const int MAX_N=1001;

enum
{
    UNWATCHED,WATCHED,INSTALLED
}; 

vector<int> adj[MAX_N];
vector<bool> visited;
int install;

int dfs(int here)
{
    visited[here]=true;
    int children[3]={0,0,0};
    for(int i=0;i<adj[here].size();++i)
    {
        int there=adj[here][i];
        if(!visited[there])
            children[dfs(there)]++;
    }
    
    if(children[UNWATCHED])
    {
        ++install;
        return INSTALLED;
    }
    if(children[INSTALLED])
        return WATCHED;
    return UNWATCHED;
}


int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int g,h;
        cin>>g>>h;
        
        visited=vector<bool>(g,false);
        install=0;
        
        for(int i=0;i<h;++i)
        {
            int a,b;
            cin>>a>>b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        
        for(int i=0;i<g;++i)
            if(!visited[i] && dfs(i)==UNWATCHED)
                install++;
        
        cout<<install<<endl;
        
        for(int i=0;i<g;++i)
            adj[i].clear();
    }

    return 0;
}
