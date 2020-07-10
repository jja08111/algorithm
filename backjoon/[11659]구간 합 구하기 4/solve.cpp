#include <iostream>
#include <vector>
using namespace std;

struct PSQ {
    int n;
    vector<int> pSum;
    PSQ(const vector<int>& array) {
        n=array.size();
        pSum.resize(4*n);
        init(array,0,n-1,1);
    }
    int init(const vector<int>& array, int left, int right, int node) {
        if(left==right)
            return pSum[node]=array[left];
        
        int mid=(left+right)/2;
        int leftSum=init(array,left,mid,node*2);
        int rightSum=init(array,mid+1,right,node*2+1);
        return pSum[node]=leftSum+rightSum;
    }
    int query(int left, int right, int node, int nodeLeft, int nodeRight)
    {
        if(right<nodeLeft || nodeRight<left)
            return 0;
        
        if(left<=nodeLeft && nodeRight<=right)
            return pSum[node];
        
        int mid=(nodeLeft+nodeRight)/2;
        return query(left,right,node*2,nodeLeft,mid)+query(left,right,node*2+1,mid+1,nodeRight);
    }
    int query(int left, int right) {
        return query(left,right,1,0,n-1);
    }
};

int main()
{
    int n,m;
    cin>>n>>m;
    
    vector<int> perm(n);
    for(int i=0;i<n;++i)
        scanf("%d",&perm[i]);
    
    PSQ pSum(perm);
    for(int i=0;i<m;++i)
    {
        int a,b;
        scanf("%d %d",&a,&b);
        printf("%d\n",pSum.query(a-1,b-1));
    }
    
    return 0;
}
