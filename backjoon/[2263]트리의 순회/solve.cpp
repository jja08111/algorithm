#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

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

int main()
{
    int n;
    
    cin>>n;
    for(int i=0;i<n;++i)
    {
        int tmp;
        scanf("%d",&tmp);
        inorder.push_back(tmp);
    }
    for(int i=0;i<n;++i)
    {
        int tmp;
        scanf("%d",&tmp);
        postorder.push_back(tmp);
    }
    for(int i=0;i<n;++i)
        position[inorder[i]]=i;
    
    printPreorder(make_pair(0,n),make_pair(0,n));
    
    return 0;
}
