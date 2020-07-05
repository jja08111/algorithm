#include <iostream>
#include <vector>
#include <utility>
using namespace std;

struct Node {
    int key;
    Node* left, *right;
    Node(const int& _key) : key(_key), left(NULL), right(NULL) {}
};

typedef pair<Node*,Node*> NodePair;

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

int main()
{
    Node* root=NULL;
    int n;
    while(cin>>n)
        root=insert(root,new Node(n));
    
    printPostorder(root);
    
    return 0;
}
