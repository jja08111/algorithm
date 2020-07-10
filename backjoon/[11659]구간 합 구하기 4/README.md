# 해결 
부분합을 이용하여 충분히 해결할 수 있는 문제였으나 종만북을 공부하며 배운 클래스를 이용해보고 싶어 다르게 구현했다.  
클래스로 노드에 해당 구간의 합을 저장하는 구간 트리를 구현했다.   

생성자를 통해 바로 부분합이 초기화 되며 초기화 시 기저사례로 리프에 도달한 경우로 설정했다.  
부분합을 구현한 후에는 실제로 탐색하는 쿼리함수가 필요하다.  
이 쿼리함수는 node 노드의 구간과 찾고자 하는 구간의 교집합이 어떤 상태인지에 따라 값을 반환한다.  
- 교집합이 공집합인 경우: 부분합은 0이다. 
- node 노드의 구간이 찾고자 하는 구간에 포함되는 경우: 구해놓은 값을 반환한다.  
- 이 외의 경우: 왼쪽과 오른쪽 자손을 재귀 호출하여 해결한다.  
```c++
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
```
