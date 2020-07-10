# 해결 
전체 높이들을 이용하여 구간 내의 최대값과 최소값을 구해 두 값의 차이를 구하는 문제이다.  
단순히 해결하면 구간이 나올 때마다 반복문으로 최대값과 최소값을 찾아나갈 수 있다.  
하지만 이 방법으로는 이 문제의 입력 값의 수를 감당할 수 없다.  

구간에 대한 질문을 빠르게 계산할 수 있는 구간 트리를 이용하면 해결할 수 있다.  
프로그래밍 대회에서 사용되는 구간 트리는 아래로 갈수록 구간을 반으로 나눠가고 노드마다 해당 구간에 대한 계산결과를 저장한다.  
이 문제에 적용하면 노드마다 해당 구간의 최소값을 저장하는 방식으로 구현하면 된다.  
최대값의 경우에는 모든 높이 값에 대해 음수를 취해준 뒤 최소값을 저장하고 계산시 다시 음수를 취해주면 최대값을 얻을 수 있다.  

구간 트리는 거의 이진 트리이기 때문에 배열을 이용하여 노드들을 저장한다.  
루트 노드를 배열의 1번 원소로 저장하고 노드 i의 왼쪽 자손과 오른쪽 자손을 각각 2xi와 2xi+1번 원소로 표현한다.  
아래로 갈수록 반으로 나눠지기 때문에 구간 트리의 인덱스는 배열의 길이 n에 대해 4를 곱하면 충분히 표현할 수 있으나 공간이 낭비된다.  

### 구간 트리 초기화 
재귀적으로 구간 트리를 형성하는 함수를 구현할 수 있다.  
루트 노드에서 부터 오른쪽과 왼쪽으로 구간을 동적으로 계산해 나아가며 최소값을 구한다.  
리프에 도달한 경우 해당 위치의 높이값을 반환하고 왼쪽과 오른쪽 자식 구간의 최소값 중 더 작은 값을 저장해 나간다.  
```c++
struct RMQ {
    int n;
    // 각 구간의 최소치
    vector<int> rangeMin;
    
    RMQ(const vector<int>& array) {
        n=array.size();
        // 배열의 길이 n에 대해 필요한 노드의 수 만큼 확보
        rangeMin.resize(n*4);
        init(array,0,n-1,1);
    }
    // node 노드가 array[left..right] 배열을 표현할 때
    // node를 루트로 하는 서브트리를 초기화하고, 이 구간의 최소치를 반환한다.
    int init(const vector<int>& array, int left, int right, int node)
    {
        // 기저사례: 리프에 도달한 경우
        if(left==right)
            return rangeMin[node]=array[left];
        
        int mid=(left+right)/2;
        int leftMin=init(array,left,mid,node*2);
        int rightMin=init(array,mid+1,right,node*2+1);
        //왼쪽과 오른쪽 자식 구간의 최소값중 더 작은 값을 저장
        return rangeMin[node]=min(leftMin,rightMin);
    }
}
```


### 구간 트리의 질의 처리 
초기화를 끝내면 이제 원하는 구간 내에서 값을 찾기 위한 준비를 해야한다.  
그러기 위해서는 아래와 같은 함수를 구현해야 한다.  
- query(left, right, node, nodeLeft, nodeRIght) = node가 표현하는 범위 [nodeLeft, nodeRight]와  
최소치를 찾기 원하는 구간 [left, right]의 교집합의 최소 원소를 반환한다.  
만약 전체가 9번 표지판까지 있을때 2번 표지판부터 3번 표지판까지의 최소값을 찾는 경우 query(2,3,1,0,9-1)로 구할 수 있다.  
query()는 우선 node가 표현하는 구간과 찾고자 하는 구간의 교집합을 구한 뒤, 그에따라 서로 다른 값을 반환한다.  
1. 교집합이 공집합인 경우: 찾고자하는 구간과 노드가 표현하는 구간이 전혀 겹치지 않으므로 무시하기 위해 INF를 반환한다.  
2. 교집합이 노드가 표현하는 구간인 경우: 현재 찾고자 하는 구간이 노드가 표현하는 집합을 완전히 포함하니 이 노드에 미리 계산한 최소치를 반환한다.  
3. 이 외의 경우: 두 개의 자손 노드에 대해 재귀 호출한 뒤, 이 두 값 중 더 작은 값을 반환한다.  
```c++
struct RMQ {
    //.. 생략 ..
    // node가 표현하는 범위 array[nodeLeft...nodeRight]가 주어질 때
    // 이 범위와 array[left...right]의 교집합의 최소치를 구한다.
    int query(int left, int right, int node, int nodeLeft, int nodeRight)
    {
        // 구하려는 구간과 현재 노드의 구간이 겹치지 않을 때
        if(right<nodeLeft || nodeRight<left)
            return INT_MAX;
        
        // 구하려는 구간이 현재 노드가 표현하는 구간을 포함할 때 
        if(left<=nodeLeft && nodeRight<=right)
            return rangeMin[node];
        
        // 양쪽 구간을 나눠서 푼 뒤 결과를 합친다.
        int mid=(nodeLeft+nodeRight)/2;
        return min(query(left, right, node*2, nodeLeft, mid),
                   query(left, right, node*2+1, mid+1, nodeRight));
    }
    // query()를 외부에서 호출하기 위한 인터페이스
    int query(int left, int right)
    {
        return query(left,right,1,0,n-1);
    }
};
```

### 구간 트리를 이용한 문제 해결 
위와 같은 클래스를 구현하면 쉽게 문제를 해결할 수 있다.  
```c++
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
        
        for(int i=0;i<N;++i)
            h[i]*=-1;
        RMQ maxLevel(h);
        
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
```
