# 해결 
원소를 삽입했을때 해당 원소가 좌측으로 몇 칸 움직이는지는 새로 삽입된 원소보다 큰 수가 몇 개인지를 알면 된다.  
이러한 계산을 간단히 하려면 새로운 원소가 삽입되면 해당 원소보다 큰 원소의 개수를 계산하고 새로운 원소를 트리에 추가시키면 된다.  
이때 트리는 펜윅트리를 이용하면 부분합을 쉽게 구할 수 있다.  
```c++
long long countMoves(const vector<int>& A)
{
    // 수의 범위가 0부터 999999까지이다.  
    FenwickTree tree(1000000);
    long long ret=0;
    for(int i=0;i<A.size();++i)
    {
        // 새로 삽입될 수보다 큰 수의 갯수를 더한다.  
        ret+=tree.sum(999999)-tree.sum(A[i]);
        tree.add(A[i],1);
    }
    return ret;
}
```
위와 같은 방법은 수의 범위가 작기 때문에 이용가능한 것이다.  

# 회고 
펜윅트리를 구현시 pos를 ++연산을 하지 않아 시간초과가 일어났다.  
그 이유를 분석해보니 0이 수열에 있을 경우 비트 연산이 제대로 되지 않기 때문이었다.  
```c++
struct FenwickTree 
{
    vector<int> tree;
    FenwickTree(int n) : tree(n+1) {}
    int sum(int pos) 
    {
        ++pos; ///////////////
        int ret=0;
        while(pos>0) 
        {
            ret+=tree[pos];
            pos&=(pos-1);
        }
        return ret;
    }
    void add(int pos, int val) 
    {
        ++pos; ////////////////
        while(pos<tree.size()) 
        {
            tree[pos]+=val;
            pos+=(pos&-pos);
        }
    }
};
```
