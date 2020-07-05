# 해결 
이진 검색 트리가 루트를 기준으로 왼쪽 서브트리는 작은 키 값들이 오른쪽 서브트리는 큰 키 값들이 들어간다.  
그리고 전위 순회 결과가 주어지니 맨 앞의 값은 루트가 된다.  
이러한 부분들을 이용하여 재귀적으로 트리를 생성하고 후위 순회 결과를 출력시키면 문제를 해결할 수 있다.  
```c++
struct Node {
    int key;
    Node* left, *right;
    Node(const int& _key) : key(_key), left(NULL), right(NULL) {}
};

Node* insert(Node* root, Node* node)
{
    if(root==NULL)
        return node;
    
    if(node->key < root->key)
        root->left=insert(root->left,node);
    else
        root->right=insert(root->right,node);
    
    return root;
}

void printPostorder(Node* root)
{
    if(root==NULL)
        return;
    
    printPostorder(root->left);
    printPostorder(root->right);
    printf("%d \n",root->key);
}
```
