# 해결 
[Fenwick Tree](https://www.acmicpc.net/blog/view/21)를 이용하여 해결했다.   
구간 안의 수를 업데이트 할 때 주의할 점은 psum.sum(b)-psum.sum(b-1)으로 해당 위치의 값을 정확히 얻어야 한다는 것이다.  
왜냐하면 psum.tree[b] 으로 착각하여 구할 경우 구간합 값이 반환될 수 있기 때문이다.  
```c++
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
        scanf("%d %lld %lld",&choice,&b,&c);
        
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
```
