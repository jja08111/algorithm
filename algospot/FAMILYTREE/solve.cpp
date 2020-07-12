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
// trip에서 노드가 처음으로 등장하는 위치 저장, 노드의 깊이 저장(index는 node이다!!)
int locInTrip[MAX_N], depth[MAX_N];
int nextSerial;

void traverse(int here, int d, vector<int>& trip)
{
    // 첫 방문시 바로 일련 번호 부여
    no2serial[here]=nextSerial;
    serial2no[nextSerial]=here;
    ++nextSerial;
    // 현재 노드의 깊이 저장
    depth[here]=d;
    // trip에서 here노드가 처음 등장하는 위치를 저장
    locInTrip[here]=trip.size();
    trip.push_back(no2serial[here]);
    // 모든 자식 노드를 방문
    for(int i=0;i<child[here].size();++i)
    {
        traverse(child[here][i],d+1,trip);
        // 자식 노드를 방문하고 현재 노드로 돌아올 때마다 다시 추가하기
        trip.push_back(no2serial[here]);
    }
}

RMQ* prepareRMQ()
{
    nextSerial=0;
    // 순회 과정에서 만나는 노드들의 일련번호를 담는다.
    vector<int> trip;
    traverse(0,0,trip);
    return new RMQ(trip);
}

int distance(RMQ* rmq, int u, int v)
{
    // trip 배열에서 u와 v의 첫 출현 위치를 찾는다.  
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
