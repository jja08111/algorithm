#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

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

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int nodeNum;
        cin>>nodeNum;
        vector<int> preorder(nodeNum), inorder(nodeNum);
        for(int i=0;i<nodeNum;++i)
            cin>>preorder[i];
        for(int i=0;i<nodeNum;++i)
            cin>>inorder[i];
        
        printPostOrder(preorder,inorder);
        cout<<endl;
    }

    return 0;
}
