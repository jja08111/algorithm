#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N=100001;
const int INT_MAX=numeric_limits<int>::max();

struct RMQ {
    int n;
    vector<int> rangeMin;
    RMQ(const vector<int>& array) {
        n=array.size();
        rangeMin.resize(4*n);
        init(array,1,0,n-1);
    }
    int init(const vector<int>& array, int node, int left, int right) {
        if(left==right)
            return rangeMin[node]=array[left];
        int mid=(left+right)/2;
        int leftMin=init(array,node*2,left,mid);
        int rightMin=init(array,node*2+1,mid+1,right);
        return rangeMin[node]=min(leftMin,rightMin);
    }
    int query(int left, int right, int node, int nodeLeft, int nodeRight) {
        if(right<nodeLeft || nodeRight<left)
            return INT_MAX;
        if(left<=nodeLeft && nodeRight<=right)
            return rangeMin[node];
        int mid=(left+right)/2;
        return min(query(left,right,node*2,nodeLeft,mid),query(left,right,node*2+1,mid+1,nodeRight));
    }
    int query(int left, int right) {
        return query(left,right,1,0,n-1);
    }
};

vector<int> adj[MAX_N];
bool visited[MAX_N];
int serial2no[MAX_N], no2serial[MAX_N];
int locInTrip[MAX_N], depth[MAX_N];
int nextSerial;

void traverse(int here, int d, vector<int>& trip)
{
    visited[here]=true;
    
    no2serial[here]=nextSerial;
    serial2no[nextSerial]=here;
    ++nextSerial;
    
    depth[here]=d;
    locInTrip[here]=trip.size();
    trip.push_back(no2serial[here]);
    
    for(int i=0;i<adj[here].size();++i)
    {
        int cand=adj[here][i];
        if(!visited[cand])
        {
            traverse(cand,d+1,trip);
            trip.push_back(no2serial[here]);
        }
    }
}

RMQ* prepareRMQ() 
{
    nextSerial=0;
    vector<int> trip;
    traverse(1,0,trip);
    return new RMQ(trip);
}

int distance(RMQ* rmq, int u, int v)
{
    int lu=locInTrip[u], lv=locInTrip[v];
    if(lu>lv)
        swap(lu,lv);
    int lca=serial2no[rmq->query(lu,lv)];
    return depth[u]+depth[v]-2*depth[lca];
}

int main()
{
    int n,m;
    cin>>n;
    for(int i=0;i<n-1;++i)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    RMQ* rmq=prepareRMQ();
    cin>>m;
    for(int i=0;i<m;++i)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        printf("%d\n",distance(rmq,u,v));
    }
    return 0;
}
