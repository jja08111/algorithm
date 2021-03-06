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
