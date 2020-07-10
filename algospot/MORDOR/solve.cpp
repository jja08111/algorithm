#include <iostream>
#include <vector>
#include <limits>
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

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int N,Q;
        scanf("%d %d",&N,&Q);
        vector<int> h(N);

        for(int i=0;i<N;++i)
            scanf("%d",&h[i]);
        
        RMQ minLevel(h);
        minLevel.init(h,0,N-1,1);
        
        for(int i=0;i<N;++i)
            h[i]*=-1;
        RMQ maxLevel(h);
        maxLevel.init(h,0,N-1,1);
        
        for(int i=0;i<Q;++i)
        {
            int a,b;
            scanf("%d %d",&a,&b);
            int minRet=minLevel.query(a,b);
            int maxRet=-maxLevel.query(a,b);
            printf("%d\n",maxRet-minRet);
        }
    }

    return 0;
}
