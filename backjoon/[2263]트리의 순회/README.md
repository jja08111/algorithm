# 해결 
후위 순회 결과에서 마지막 값이 집합의 루트인 것과 
이 루트 값이 중위 순회 결과에서 왼쪽 트리와 오른쪽 트리를 나누는 기준이 된다는 특징을 이용하여 해결하면 된다.  

메모리 초과에 유의해야 하는 문제이다.  
함수 호출할 때마다 배열을 매개변수로 넘기면 너무 많은 메모리가 낭비되어 실패한다.  
그래서 수열을 넘기지 않고 범위를 매개변수로 하여 해결하면 된다.  

작은 팁으로 find함수로 중위 순회 결과에 root 위치를 찾기 보다는 position이라는 역함수를 만들어 두면 꽤 많은 속도 향상을 얻을 수 있다.  
```c++
vector<int> inorder,postorder;
int position[100001];

void printPreorder(pair<int,int> in, pair<int,int> post)
{
    const int n=in.second-in.first;
    if(n==0)
        return;
    
    const int root=postorder[post.second-1];
    const int ls=position[root]-in.first;
    
    printf("%d ",root);
    printPreorder({in.first, in.first+ls}, {post.first, post.first+ls});
    printPreorder({in.first+ls+1, in.second}, {post.first+ls, post.second-1});
}
```
