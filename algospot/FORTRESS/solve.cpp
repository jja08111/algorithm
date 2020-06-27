#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
    vector<TreeNode*> children;
};

int n, y[100], x[100], radius[100];

int sqr(int x) 
{
    return x*x;
}

int sqrdist(int a, int b) 
{
    return sqr(y[a]-y[b])+sqr(x[a]-x[b]);
}

//성벽 a가 b를 포함하는지 확인
bool encloses(int a, int b)
{
    return radius[a]>radius[b] && sqrdist(a,b)<sqr(radius[a]-radius[b]);
}

bool isChild(int parent, int child)
{
    if(!encloses(parent,child))
        return false;
    
    //parent가 child성벽을 직접 포함 하지 않는 경우
    for(int i=0;i<n;++i)
        if(i!=parent && i!=child && encloses(parent,i) && encloses(i,child))
            return false;
    
    return true;
}

TreeNode* getTree(int root)
{
    TreeNode* ret=new TreeNode();
    for(int ch=0;ch<n;++ch)
        if(isChild(root,ch))
            ret->children.push_back(getTree(ch));
    return ret;
}

int longest;

//root를 루트로 하는 서브트리의 높이를 반환한다.
int getHeight(TreeNode* root)
{
    //각 자식을 루트로 하는 서브트리의 높이를 계산한다.
    vector<int> heights;
    for(int i=0;i<root->children.size();++i)
        heights.push_back(getHeight(root->children[i]));
    
    if(heights.empty())
        return 0;
    
    sort(heights.begin(), heights.end());
    
    //root를 최상위 노드로 하는 경로를 고려
    if(heights.size()>=2)
        longest=max(longest, 2+heights[heights.size()-1]+heights[heights.size()-2]);
    
    //트리의 높이는 서브트리 높이의 최대치에 1을 더한다.
    return heights.back()+1;
}

int solve(TreeNode* root)
{
    longest=0;
    int h=getHeight(root);
    return max(longest,h);
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>n;
        for(int i=0;i<n;++i)
            cin>>x[i]>>y[i]>>radius[i];
        
        TreeNode* root=getTree(0);
        cout<<solve(root)<<endl;
    }

    return 0;
}
