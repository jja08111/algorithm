# 해결 
트리 구조를 어떻게 만들지 쉽게 떠오르지 않았다.  
인덱스가 A~Z이니 26개의 노드와 자식 0, 1번 배열을 선언했다.  
인덱스가 노드이고 자식은 문자를 저장해서 가르키는 방식을 선택했다.  

출력은 전위 순회일때 출력하고 다음 자식을 방문하는 방식이다.  
여기서 자식이 없는 경우를 '.'으로 표현했기 때문에 '.'을 만나면 바로 함수를 종료해야 한다.  
```c++
char node[26][2]={'.',};

void preorder(char root)
{
    if(root=='.')
        return;
    cout<<root;
    preorder(node[root-'A'][0]);
    preorder(node[root-'A'][1]);
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
```
