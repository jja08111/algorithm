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
