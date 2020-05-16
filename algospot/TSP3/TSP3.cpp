#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <bitset>

const double INF=1e200;
const int MAX=20;
const int CACHE_DEPTH=5;

vector<int> nearest[MAX];
// 간선의 길이, 간선의 두 정점
vector<pair<double,pair<int,int> > > edges;
double dist[MAX][MAX];
double minEdge[MAX];
map<int,double> cache[MAX][CACHE_DEPTH+1];
int n;
double best;

struct DisjointSet
{
    int vilageNum, components;
    vector<int> parent,rank;
    
    DisjointSet(int n) : vilageNum(n), components(n), parent(n), rank(n)
    {
        for(int i=0;i<vilageNum;++i)
        {
            parent[i]=i;
            rank[i];
        }
    }
    //here가 포함된 집합의 대표를 반환
    int find(int here)
    {
        if(here==parent[here])
            return here;
        return parent[here]=find(parent[here]);
    }
    //a가 포함된 집합과 b가 포함된 집합을 합치고, 합칠수 있으면 참을 반환
    bool merge(int a, int b)
    {
        a=find(a);
        b=find(b);
        if(a==b)
            return false;
        if(rank[a]>rank[b])
            swap(a,b);
        parent[a]=b;
        if(rank[a]==rank[b])
            ++rank[b];
        components--;
        return true;
    }
};


double solve()
{
    edges.clear();
    for(int i=0;i<n;++i)
        for(int j=0;j<i;++j)
            edges.push_back(make_pair(dist[i][j],make_pair(i,j)));
    sort(edges.begin(),edges.end());
    //생략
}

bool pathSwapPruning(const vector<int>& path)
{
    if(path.size()<4) return false;
    int p=path[path.size()-4];
    int a=path[path.size()-3];
    int b=path[path.size()-2];
    int q=path[path.size()-1];
    return dist[p][a]+dist[b][q]
}

bool pathReversePruning(const vector<int>& path)
{
    if(path.size()<4) return false;
    int b=path[path.size()-2];
    int q=path[path.size()-1];
    for(int i=0;i+3<path.size();++i)
    {
        int p=path[i];
        int a=path[i+1];
        if(dist[p][a]+dist[b][q]>dist[p][b]+dist[a][q])
            return true;
    }
    return false;
}

double mstHeuristic(int here, const vector<bool>& visited)
{
    DisjointSet sets(n);
    double taken=0;
    for(int i=0;i<edges.size();++i)
    {
        int a=edges[i].second.first;
        int b=edges[i].second.second;
        if(a!=0 && a!=here && visited[a]) continue;
        if(b!=0 && b!=here && visited[b]) continue;
        if(sets.merge(a,b))
            taken+=edges[i].first;
    }
    return taken;
}

double dp(int here, int visited)
{
    if(visited==(1<<n)-1)
        return dist[here][0];
    
    int remaining=n-__builtin_popcount(visited);
    double& ret=cache[here][remaining][visited];
    if(ret>0)
        return ret;
    
    ret=INF;
    for(int next=0;next<n;++next)
    {
        if(visited&(1<<next))
            continue;
        ret=min(ret,dp(next,visited+(1<<next))+dist[here][next]);
    }
    return ret;
}

void search(vector<int>& path, int visited, double currentLength)
{
    int here=path.back();
    
    if(pathReversePruning(path))
        return;
    
    if(best<=currentLength+mstHeuristic(here,visited))
        return;
    
    if(path.size()+CACHE_DEPTH>=n)
    {
        double candidate=currentLength+dp(here,visited);
        best=min(best,candidate);
        return;
    }
    
    double ret=INF;
    for(int i=0;i<nearest[here].size();++i)
    {
        int next=next[here][i];
        if(visited&(1<<next))
            continue;
        
        path.push_back(next);
        search(path,visited+(1<<next),currentLength+dist[here][next]);
        path.pop_back();
    }
}

double solve()
{
    //nearest 초기화
    for(int i=0;i<n;++i)
    {
        vector<pair<double,int> > order;
        for(int j=0;j<n;++j)
            if(i!=j)
                order.push_back(make_pair(dist[i][j],j));
        sort(order.begin(),order.end());
        nearest[i].clear();
        for(int j=0;j<n-1;++j)
            nearest[i].push_back(order[j].second);
    }
    
    //edges 초기화
    edges.clear();
    for(int i=0;i<n;++i)
        for(int j=0;j<i;++j)
            edges.push_back(make_pair(dist[i][j],make_pair(i,j)));
    sort(edges.begin(),edges.end());
    
    for(int i=0;i<MAX;++i)
        for(int j=0;j<=CACHE_DEPTH;j++)
            cache[i][j].clear();
    
    best=INF;
    for(int i=0;i<n;++i)
    {
        vector<int> path(1,i);
        int visited=(1<<i);
        search(path,visited,0);
    }
    
    return best;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>n;
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                cin>>dist[i][j];
        
        printf("%.10lf \n",solve());
    }

    return 0;
}
