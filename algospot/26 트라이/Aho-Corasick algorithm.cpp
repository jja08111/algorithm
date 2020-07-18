#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int ALPHABETS=26;
int toNumber(char ch) { return ch-'A'; }

struct TrieNode {
    TrieNode* children[ALPHABETS];
    int terminal;
    TrieNode* fail;
    vector<int> output;
    int first;
    TrieNode() : terminal(-1), first(-1) {
        memset(children,0,sizeof(children));
    }
    ~TrieNode() {
        for(int i=0;i<ALPHABETS;++i)
            if(children[i])
                delete children[i];
    }
    void insert(const char* key, int id) {
        if(first==-1)
            first=id;
        if(*key==0)
            terminal=id;
        else {
            int next=toNumber(*key);
            if(children[next]==NULL)
                children[next]=new TrieNode();
            children[next]->insert(key+1,id);
        }
    }
    TrieNode* find(const char* key) {
        if(*key==0)
            return this;
        int next=toNumber(*key);
        if(children[next]==NULL)
            return NULL;
        return children[next]->find(key+1);
    }
    int type(const char* key, int id) {
        if(*key==0)
            return 0;
        if(first==id)
            return 1;
        int next=toNumber(*key);
        return 1+children[next]->type(key+1,id);
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
        for(int edge=0;edge<ALPHABETS;++edge)
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
            child->output=child->fail->output;
            if(child->terminal!=-1)
                child->output.push_back(child->terminal);
            q.push(child);
        }
    }
}

vector<pair<int,int> > ahoCorasick(const string& s, TrieNode* root)
{
    vector<pair<int,int> > ret;
    TrieNode* state=root;
    for(int i=0;i<s.size();++i)
    {
        int chr=toNumber(s[i]);
        while(state!=root && state->children[chr]==NULL)
            state=state->fail;
        if(state->children[chr])
            state=state->children[chr];
        for(int j=0;j<state->output.size();++j)
            ret.push_back(make_pair(i,state->output[j]));
    }
    return ret;
}
