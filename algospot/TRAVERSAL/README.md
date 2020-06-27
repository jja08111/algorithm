# 해결 
난이도는 '하'였으나 생각보다 어려운 문제였다.  
전위, 중위, 후위 순회의 의미를 정확히 이해해야 풀수 있는 문제이다.  
전위 순회는 루트를 방문하고 왼쪽 서브트리, 오른쪽 서브트리 순서로 방문한다.  
중위 순회는 왼쪽 서브트리를 방문하고 루트, 오른쪽 서브트리 순서로 방문한다.  
후위 순회는 왼쪽, 오른쪽 서브트리를 방문한 다음에 루트를 방문한다.  

이를 재귀적으로 접근하면 꽤 간단하게 구현할 수 있다.  
전위, 중위 순회를 통해서 후위 순회를 출력해야 한다.  
전위 순회는 맨 앞에 있는 노드가 루트이다.  
이를 통해 중위 순회는 루트를 기준으로 왼쪽 서브트리 오른쪽 서브트리로 나누어져 있으므로 각각의 서브트리의 크기를 구할 수 있다.  
서브트리를 모두 접근하고 마지막에 루트를 출력하면 된다.  

예를 들어 
- 전위 순회{27 16 9 12 54 36 72}
- 중위 순회{9 12 16 27 36 54 72}

가 있을 때 27은 트리의 루트이고 이를 중위 순회 결과에서 위치를 찾으면 3이다. 따라서 이 값이 왼쪽 서브트리의 크기가 되고  
오른쪽 서브트리는 전체 크기에서 왼쪽 부분과 루트를 뺀 값 즉, 7-3-1=3 이다.  
이 다음 왼쪽 서브트리와 오른쪽 서브트리로 slice 해서 방문 할 수 있다.  
```c++

//벡터를 구간 [a,b)로 자른다.
vector<int> slice(const vector<int>& v, int a, int b)
{
    return vector<int>(v.begin()+a, v.begin()+b);
}

void printPostOrder(const vector<int>& preorder, const vector<int>& inorder)
{
    const int N=preorder.size();
    
    //기저 사례: 트리가 텅 빈 경우
    if(preorder.empty())
        return;
    
    const int root=preorder[0];
    //루트 왼쪽, 오른쪽의 서브트리 크기를 구한다
    const int L=find(inorder.begin(),inorder.end(),root)-inorder.begin();
    const int R=N-1-L;
    
    printPostOrder(slice(preorder,1,1+L), slice(inorder,0,L));
    printPostOrder(slice(preorder,1+L,N), slice(inorder,L+1,N));
    //후위 순회이니 루트를 마지막에 출력한다.
    cout<<root<<' ';
}
```
