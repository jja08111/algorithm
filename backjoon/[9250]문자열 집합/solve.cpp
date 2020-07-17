#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int ALPHABET=26;
int toNumber(char ch) { return ch-'a'; }

struct TrieNode {
    TrieNode* children[ALPHABET];
    int terminal;
    // 실패 연결
    TrieNode* fail;
    vector<int> output;
    TrieNode() : terminal(-1) {
        memset(children,0,sizeof(children));
    }
    ~TrieNode() {
        for(int i=0;i<ALPHABET;++i)
            if(children[i])
                delete children[i];
    }
    void insert(const char* key, int id) {
        if(*key==0)
            terminal=id;
        else {
            int next=toNumber(*key);
            if(children[next]==NULL)
                children[next]=new TrieNode();
            children[next]->insert(key+1,id);
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
            child->output=child->fail->output;
            if(child->terminal!=-1)
                child->output.push_back(child->terminal);
            q.push(child);
        }
    }
}

bool ahoCorasick(const string& s, TrieNode* root)
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
        
        ret+=state->output.size();
    }
    return ret>0;
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
        trie->insert(buf,i);
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
