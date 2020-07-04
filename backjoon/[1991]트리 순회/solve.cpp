#include <iostream>
using namespace std;

char node[26][2]={'.',};

void preorder(char root)
{
    if(root=='.')
        return;
    cout<<root;
    preorder(node[root-'A'][0]);
    preorder(node[root-'A'][1]);
}

void inorder(char root)
{
    if(root=='.')
        return;
    inorder(node[root-'A'][0]);
    cout<<root;
    inorder(node[root-'A'][1]);
}

void postorder(char root)
{
    if(root=='.')
        return;
    postorder(node[root-'A'][0]);
    postorder(node[root-'A'][1]);
    cout<<root;
}

int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;++i)
    {
        char tmp;
        cin>>tmp;
        cin>>node[tmp-'A'][0]>>node[tmp-'A'][1];
    }
    
    preorder('A');
    cout<<endl;
    inorder('A');
    cout<<endl;
    postorder('A');
    cout<<endl;

    return 0;
}
