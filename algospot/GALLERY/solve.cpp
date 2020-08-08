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
int installed, galleryNum;

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
        ++installed;
        return INSTALLED;
    }
    if(children[INSTALLED])
        return WATCHED;
    return UNWATCHED;
}

int installCamera()
{
    visited=vector<bool>(galleryNum,false);
    installed=0;
    
    for(int i=0;i<galleryNum;++i)
        if(!visited[i] && dfs(i)==UNWATCHED)
            installed++;
    
    return installed;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int hallNum;
        cin>>galleryNum>>hallNum;
        
        for(int i=0;i<hallNum;++i)
        {
            int a,b;
            cin>>a>>b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        
        int ret=installCamera();
        
        cout<<ret<<endl;
        
        for(int i=0;i<galleryNum;++i)
            adj[i].clear();
    }

    return 0;
}
