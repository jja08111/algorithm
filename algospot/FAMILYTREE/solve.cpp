#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INT_MAX=numeric_limits<int>::max();

struct RMQ {
    int n;
    vector<int> rangeMin;
    
    RMQ(const vector<int>& array) {
        n=array.size();
        rangeMin.resize(n*4);
        init(array,0,n-1,1);
    }
    int init(const vector<int>& array, int left, int right, int node)
    {
        if(left==right)
            return rangeMin[node]=array[left];
        
        int mid=(left+right)/2;
        int leftMin=init(array,left,mid,node*2);
        int rightMin=init(array,mid+1,right,node*2+1);
        return rangeMin[node]=min(leftMin,rightMin);
    }
    
    int query(int left, int right, int node, int nodeLeft, int nodeRight)
    {
        if(right<nodeLeft || nodeRight<left)
            return INT_MAX;
        
        if(left<=nodeLeft && nodeRight<=right)
            return rangeMin[node];
        
        int mid=(nodeLeft+nodeRight)/2;
        return min(query(left, right, node*2, nodeLeft, mid),
                   query(left, right, node*2+1, mid+1, nodeRight));
    }
    int query(int left, int right)
    {
        return query(left,right,1,0,n-1);
    }
};

const int MAX_N=100000;
int n;
vector<int> child[MAX_N];
int no2serial[MAX_N], serial2no[MAX_N];
int locInTrip[MAX_N], depth[MAX_N];
int nextSerial;

void traverse(int here, int d, vector<int>& trip)
{
    no2serial[here]=nextSerial;
    serial2no[nextSerial]=here;
    ++nextSerial;
    depth[here]=d;
    // trip에서 here노드가 처음 등장하는 위치를 저장
    locInTrip[here]=trip.size();
    trip.push_back(no2serial[here]);
    for(int i=0;i<child[here].size();++i)
    {
        traverse(child[here][i],d+1,trip);
        trip.push_back(no2serial[here]);
    }
}

RMQ* prepareRMQ()
{
    nextSerial=0;
    vector<int> trip;
    traverse(0,0,trip);
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
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        for(int i=0;i<MAX_N;++i)
            child[i].clear();
        
        int q;
        scanf("%d %d",&n,&q);
        for(int i=1;i<n;++i)
        {
            int father;
            scanf("%d",&father);
            child[father].push_back(i);
        }
        
        RMQ* rmq=prepareRMQ();
        for(int i=0;i<q;++i)
        {
            int u,v;
            scanf("%d %d",&u,&v);
            printf("%d\n",distance(rmq,u,v));
        }
    }
    return 0;
}
