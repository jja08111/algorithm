# 해결 
Aho-Corasick 알고리즘을 이용하여 해결했다.  
문자가 A,T,G,C 4가지가 이용되니 이들의 각각 문자에 대한 숫자를 반환하는 함수를 만들었다.  
초기에 문자열이 완성되는 노드에 output을 1로 설정했고 실패 간선을 만들 때에 해당 노드에 접미사 문자열이 있으면 갱신하였다.  

돌연변이 생성은 reverse함수를 이용하였는데 인덱스에 유의해야 했다.  

이 문제에서 주의할 점은 돌연변이와 기존 marker를 trie에 추가해야 한다는 점이다.  
또한 문제에서 4개의 글자를 이용하는데 쓸데 없이 모든 알파벳을 자식 노드로 생성하면 메모리 초과가 발생한다.  
그리고 입출력 속도가 느린 함수를 이용하면 시간초과가 발생한다.   
```c++
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_IDEX=4;

int toNumber(char ch) 
{ 
    switch(ch)
    {
    case 'A': return 0;
    case 'T': return 1;
    case 'G': return 2;
    case 'C': return 3;
    }
    return -1;
}

struct TrieNode {
    // 4개의 글자만 필요
    TrieNode* children[MAX_IDEX];
    int output;
    TrieNode* fail;
    TrieNode() : output(0) {
        memset(children,0,sizeof(children));
    }
    ~TrieNode() {
        for(int i=0;i<MAX_IDEX;++i)
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

void computeFailFunc(TrieNode* root)
{
    queue<TrieNode*> q;
    root->fail=root;
    q.push(root);
    while(!q.empty())
    {
        TrieNode* here=q.front();
        q.pop();
        for(int edge=0;edge<MAX_IDEX;++edge)
        {
            TrieNode* child=here->children[edge];
            if(!child)
                continue;
            
            // 1레벨 노드의 실패 연결은 항상 루트
            if(here==root)
                child->fail=root;
            // 아닌 경우 부모의 실패 연결을 따라가면서 실패 연결을 찾는다.
            else
            {
                TrieNode* t=here->fail;
                // 루트에 도달하지 않았거나 다음 글자(edge)로 표시된 간선이 없는 경우 반복
                while(t!=root && t->children[edge]==NULL)
                    t=t->fail;
                // edge글자가 있는 경우 해당 노드로 이동한다.
                if(t->children[edge])
                    t=t->children[edge];
                child->fail=t;
            }
            child->output+=child->fail->output;
            q.push(child);
        }
    }
}

int ahoCorasick(const string& s, TrieNode* root)
{
    int ret=0;
    TrieNode* state=root;
    for(int i=0;i<s.size();++i)
    {
        int chr=toNumber(s[i]);
        while(state!=root && state->children[chr]==NULL)
            state=state->fail;
        if(state->children[chr])
            state=state->children[chr];
        ret+=state->output;
    }
    return ret;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int n,m;
        cin>>n>>m;
        
        char dna[1000002], marker[102];
        scanf("%s %s",dna,marker);
        
        TrieNode* trie=new TrieNode();
        
        // 돌연변이를 포함한 자신도 추가해야 한다.  
        trie->insert(marker);
        for(int lo=0;lo<m-1;++lo)
            for(int hi=lo+2;hi<=m;++hi)
            {
                reverse(marker+lo,marker+hi);
                trie->insert(marker);
                reverse(marker+lo,marker+hi);
            }
        
        computeFailFunc(trie);
        
        cout<<ahoCorasick(dna,trie)<<endl;
        
        delete trie;
    }
    return 0;
}

```
