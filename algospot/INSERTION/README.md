# 해결 
문제를 손으로 풀다 보면 뒤에서부터 해결하면 된다는 아이디어를 얻을 수 있다.  
주어진 움직인 칸수를 n번째 값부터 이용하여 1번째 값까지 하나씩 삭제하고 결과 배열에 추가하여 답을 구할 수 있다.  

이때 k번째 원소를 무엇인지 찾고, 삭제하는 작업을 빠르게 하기 위해서는 Treap을 구현하여 해결하여야 한다.  
### Treap
트립은 트리와 힙을 결합한 것이다. 이진 트리에서 각 노드에 랜덤으로 우선순위를 부여하여 우선순위가 큰 순서대로 부모에 위치하게 하는 것이 핵심이다.  
트립을 직접 구현하여 k번째 원소와 특정한 값보다 작은 원소의 개수를 쉽게 구할 수 있다. 그 이유는 새로운 값이 추가될 때마다 트리의 크기를 갱신하기 때문이다.  
```c++
typedef int KeyType;

struct Node {
    KeyType key;
    int priority, size;
    
    Node *left, *right;
    Node(const KeyType& _key) : key(_key), priority(rand()), 
        size(1), left(NULL), right(NULL) {
    }
    
    void setLeft(Node* newLeft) { left=newLeft; calcSize(); }
    void setRight(Node* newRight) { right=newRight; calcSize(); }
    void calcSize() {
        size=1;
        if(left) size+=left->size;
        if(right) size+=right->size;
    }
};

typedef pair<Node*,Node*> NodePair;

NodePair split(Node* root, KeyType key)
{
    if(root==NULL)
        return NodePair(NULL,NULL);
    
    if(root->key < key)
    {
        NodePair rs=split(root->right,key);
        root->setRight(rs.first);
        return NodePair(root,rs.second);
    }
    NodePair ls=split(root->left,key);
    root->setLeft(ls.second);
    return NodePair(ls.first,root);
}

Node* insert(Node* root, Node* node)
{
    if(root==NULL)
        return node;
    
    if(root->priority < node->priority)
    {
        NodePair splitted=split(root,node->key);
        node->setLeft(splitted.first);
        node->setRight(splitted.second);
        return node;
    }
    else if(node->key < root->key)
        root->setLeft(insert(root->left,node));
    else
        root->setRight(insert(root->right,node));
    return root;
}

Node* merge(Node* a, Node* b)
{
    if(a==NULL) return b;
    if(b==NULL) return a;
    if(a->priority < b->priority)
    {
        b->setLeft(merge(a,b->left));
        return b;
    }
    a->setRight(merge(a->right,b));
    return a;
}

Node* erase(Node* root, KeyType key)
{
    if(root==NULL)
        return root;
    
    if(root->key == key)
    {
        Node* ret=merge(root->left,root->right);
        delete root;
        return ret;
    }
    if(key < root->key)
        root->setLeft(erase(root->left,key));
    else
        root->setRight(erase(root->right,key));
    return root;
}

Node* kth(Node* root, int k)
{
    int leftSize=0;
    if(root->left != NULL)
        leftSize=root->left->size;
    
    if(k<=leftSize)
        return kth(root->left,k);
    if(k==leftSize+1)
        return root;
    return kth(root->right,k-leftSize-1);
}
```

### 뒤에서부터 해결 
```c
vector<int> getOriginPerm(Node* root, vector<int>& moveCount)
{
    vector<int> ret(n);
    for(int i=n-1;i>=0;--i)
    {
        Node* here=kth(root,i-moveCount[i]);
        ret[i]=here->key;
        root=erase(root,here->key);
    }
    return ret;
}
```
