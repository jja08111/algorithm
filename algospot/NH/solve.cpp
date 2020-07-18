#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int ALPHABET=26;
int toNumber(char ch) { return ch-'a'; }

struct TrieNode 
{
    TrieNode* children[ALPHABET];
    TrieNode* fail;
    TrieNode* next[ALPHABET];
    vector<int> output;
    int terminal, no;
    
    TrieNode(): terminal(-1), fail(NULL) 
    {
        memset(children,0,sizeof(children));
    }
    ~TrieNode()
    {
        for(int i=0;i<ALPHABET;++i)
            if(children[i])
                delete children[i];
    }
    void insert(const char* key, int id)
    {
        if(*key==0)
            terminal=id;
        else
        {
            int next=toNumber(*key);
            if(children[next]==NULL)
                children[next]=new TrieNode();
            children[next]->insert(key+1,id);
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
        
        for(int edge=0;edge<ALPHABET;++edge)
        {
            TrieNode* child=here->children[edge];
            if(!child)
                continue;
            
            if(here==root)
                child->fail=root;
            else
            {
                TrieNode* failure=here->fail;
                while(failure!=root && failure->children[edge]==NULL)
                    failure=failure->fail;
                if(failure->children[edge])
                    failure=failure->children[edge];
                
                child->fail=failure;
            }
            child->output=child->fail->output;
            if(child->terminal!=-1)
                child->output.push_back(child->terminal);
            q.push(child);
        }
    }
}

void computeTransition(TrieNode* here, int& nodeCounter)
{
    here->no=nodeCounter++;
    for(int chr=0;chr<ALPHABET;++chr)
    {
        TrieNode* next=here;
        while(next!=next->fail && next->children[chr]==NULL)
            next=next->fail;
        if(next->children[chr])
            next=next->children[chr];
        here->next[chr]=next;
        if(here->children[chr])
            computeTransition(here->children[chr], nodeCounter);
    }
}

const int MOD=10007;
int cache[101][1001];

// 앞으로 length 글자를 더 만들어야 하는데, 아호-코라식 알고리즘의 
// 현재 상태가 state에 주어질 때 IDS에 걸리지 않는 문자열의 수 반환
int count(int length, TrieNode* state)
{
    // 기저 사례: 현재 상태에 IDS가 인식하는 패턴이 나온 경우
    if(state->output.size())
        return 0;
    // 기저 사례: 문자열을 전부 만든 경우
    if(length==0)
        return 1;
    
    int& ret=cache[length][state->no];
    if(ret!=-1)
        return ret;
    
    ret=0;
    // 다음으로 letter 글자를 넣을 경우
    for(int letter=0;letter<ALPHABET;++letter)
    {
        ret+=count(length-1, state->next[letter]);
        ret%=MOD;
    }
    return ret;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        TrieNode* trie=new TrieNode();
        int n,m, nodeCounter=0;
        
        cin>>n>>m;
        for(int i=0;i<m;++i)
        {
            char buf[101];
            scanf("%s",buf);
            trie->insert(buf,i);
        }
        
        memset(cache,-1,sizeof(cache));
        computeFailFunc(trie);
        computeTransition(trie,nodeCounter);
        
        cout<<count(n,trie)<<endl;
    }
    return 0;
}
