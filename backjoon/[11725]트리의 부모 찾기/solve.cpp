#include <iostream>
#include <vector>
using namespace std;

const int MAX=100001;

vector<int> tree[MAX];
int parent[MAX];
bool visited[MAX];

void getParent(int here)
{
    visited[here]=true;
    for(int there=0;there<tree[here].size();++there)
    {
        int cand=tree[here][there];
        if(!visited[cand])
        {
            parent[cand]=here;
            getParent(cand);
        }
    }
}

int main()
{
    int n;
    cin>>n;
    
    for(int i=0;i<n;++i)
    {
        int a,b;
        scanf("%d %d",&a,&b);
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    
    getParent(1);
    
    for(int i=2;i<=n;++i)
        printf("%d \n",parent[i]);
    
    return 0;
}
