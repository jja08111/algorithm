#include <iostream>
#include <vector>
using namespace std;

struct FenwickTree {
    vector<long long> tree;
    FenwickTree(long long n) : tree(n+1) {}
    long long sum(long long pos) {
        long long ret=0;
        while(pos>0) {
            ret+=tree[pos];
            pos&=(pos-1);
        }
        return ret;
    }
    void add(long long pos, long long val) {
        while(pos<tree.size()) {
            tree[pos]+=val;
            pos+=(pos&-pos);
        }
    }
};

int main()
{
    int n,m,k;
    cin>>n>>m>>k;
    
    FenwickTree psum(n);
    for(int i=1;i<=n;++i)
    {
        long long a;
        scanf("%lld",&a);
        psum.add(i,a);
    }
    
    for(int i=0;i<m+k;++i)
    {
        long long choice, b, c;
        scanf("%lld %lld %lld",&choice,&b,&c);
        
        if(choice==1)
            psum.add(b,c-(psum.sum(b)-psum.sum(b-1)));
        else
        {
            if(b>c)
                swap(b,c);
            long long ret=psum.sum(c)-psum.sum(b-1);
            printf("%lld \n",ret);
        }
    }

    return 0;
}
