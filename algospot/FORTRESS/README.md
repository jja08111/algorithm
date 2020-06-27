# 해결 
성벽의 구조를 보면 외벽을 루트로하는 트리 구조인 것을 알 수 있다.  
따라서 이 문제는 크게 2가지 과정을 커쳐야 한다.   
1. 성벽을 트리 구조로 변환
2. 트리의 가장 긴 잎과 잎 경로와 트리의 높이 중 큰 값을 찾기  

### 1. 성벽을 트리 구조로 변환 
한 성벽이 다른 성벽에 포함되려면 두 성벽의 중심의 거리 dist가 두 성벽의 반지름 차이 r보다 작아야 한다.  
```c++
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
```
그리고 트리 구조이기 때문에 한 성벽이 다른 성벽을 직접적으로 포함하는 경우만 형성해야 한다.  
```c++
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
```
아래는 외벽이 루트인 트리를 형성하는 과정을 재귀적으로 구현한 코드이다.  
```c++
struct TreeNode {
    vector<TreeNode*> children;
};

TreeNode* getTree(int root)
{
    TreeNode* ret=new TreeNode();
    for(int ch=0;ch<n;++ch)
        if(isChild(root,ch))
            ret->children.push_back(getTree(ch));
    return ret;
}
```

### 2. 트리의 가장 긴 잎과 잎 경로와 트리의 높이 중 큰 값을 찾기  
트리에서 각 자식을 루트로 하는 서브트리의 높이를 계산한 뒤  
가장 높은 서브트리 두 개의 높이를 더하면 경로가 완성된다. 여기서 현재 트리의 루트를 고려해야 하니 2를 더한다.  
이 또한 재귀적으로 계산한다.  

눈여겨 볼 부분은 가장 긴 잎과 잎 경로를 전역변수 longest를 갱신하는 방식으로 얻고 있는 부분이다.
```c++
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
```
