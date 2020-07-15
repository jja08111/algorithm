# 해결 
다른 방법이 있으나 트라이를 공부하기 위해 트라이로 해결했다.  
유의할 점은 구조체를 그냥 사용하는 경우 문자열의 부분 문자열로도 존재한다고 계산되어 오류가 발생할 수 있다.  
main함수의 if문을 변경할 수 있겠으나 구조체 내의 find함수에서 마지막 key에 도달했을 때 terminal이 true인 경우만 현재 노드를 반환하게 해서 해결했다.  
```c++
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int ALPHABETS=26;
int toNumber(char ch) { return ch-'a'; }

struct TrieNode {
    TrieNode* children[ALPHABETS];
    bool terminal;
    TrieNode() : terminal(false) {
        memset(children,0,sizeof(children));
    }
    ~TrieNode() {
        for(int i=0;i<ALPHABETS;++i)
            if(children[i])
                delete children[i];
    }
    void insert(const char* key) {
        if(*key==0)
            terminal=true;
        else {
            int next=toNumber(*key);
            if(children[next]==NULL)
                children[next]=new TrieNode();
            children[next]->insert(key+1);
        }
    }
    TrieNode* find(const char* key) {
        if(*key==0)
            return this->terminal ? this : NULL;
        int next=toNumber(*key);
        if(children[next]==NULL)
            return NULL;
        return children[next]->find(key+1);
    }
};

int main()
{
    int n,m;
    cin>>n>>m;
    
    TrieNode* trie=new TrieNode();
    
    for(int i=0;i<n;++i)
    {
        char s[501];
        scanf("%s",s);
        trie->insert(s);
    }
    
    int ret=0;
    for(int i=0;i<m;++i)
    {
        char s[501];
        scanf("%s",s);
        if(trie->find(s)!=NULL)
            ++ret;
    }
    cout<<ret<<endl;
    
    return 0;
}
```
