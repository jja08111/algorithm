# 해결 
Aho-Corasick 알고리즘을 이용하여 해결했다.  
주어진 문자열에 문자열 집합내의 문자열 1개라도 존재하면 YES를 출력하는 문제이다.  
따라서 트라이의 노드 중 문자열의 마지막에 다다른 노드는 output을 1로 설정하며 문자열의 접미사가 1인 경우 두 값을 더해 갱신했다.  

트라이에서 문자열을 찾다가 1개라도 나오는 순간 참을 반환하여 함수를 종료했다.  
```c++
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int ALPHABET=26;
int toNumber(char ch) { return ch-'a'; }

struct TrieNode {
    TrieNode* children[ALPHABET];
    // 실패 연결
    TrieNode* fail;
    int output;
    TrieNode() : output(0) {
        memset(children,0,sizeof(children));
    }
    ~TrieNode() {
        for(int i=0;i<ALPHABET;++i)
            if(children[i])
                delete children[i];
    }
    void insert(const char* key) {
        if(*key==0)
            output=1;
        else {
            int next=toNumber(*key);
            if(children[next]==NULL)
                children[next]=new TrieNode();
            children[next]->insert(key+1);
        }
    }
};

// 트라이가 주어질 때 각 노드에 대해 실패 연결과 출력 문자열 목록을 계산한다.
void computeFailFunc(TrieNode* root)
{
    queue<TrieNode*> q;
    root->fail=root;
    q.push(root);
    while(!q.empty())
    {
        TrieNode* here=q.front();
        q.pop();
        for(int edge=0;edge<ALPHABET;++edge)
        {
            TrieNode* child=here->children[edge];
            if(!child)
                continue;
            // 1레벨 노드의 실패 연결은 항상 루트
            if(here==root)
                child->fail=root;
            else
            {
                TrieNode* t=here->fail;
                while(t!=root && t->children[edge]==NULL)
                    t=t->fail;
                
                if(t->children[edge])
                    t=t->children[edge];
                child->fail=t;
            }
            child->output+=child->fail->output;
            q.push(child);
        }
    }
}

bool ahoCorasick(const string& s, TrieNode* root)
{
    TrieNode* state=root;
    for(int i=0;i<s.size();++i)
    {
        int chr=toNumber(s[i]);
        while(state!=root && state->children[chr]==NULL)
            state=state->fail;
        
        if(state->children[chr])
            state=state->children[chr];
        
        if(state->output)
            return true;
    }
    return false;
}

int main()
{
    TrieNode* trie=new TrieNode();
    int N,Q;
    
    cin>>N;
    for(int i=0;i<N;++i)
    {
        char buf[101];
        scanf("%s",buf);
        trie->insert(buf);
    }
    
    computeFailFunc(trie);
    
    cin>>Q;
    for(int i=0;i<Q;++i)
    {
        string s;
        cin>>s;
        if(ahoCorasick(s,trie))
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }
    return 0;
}
```
