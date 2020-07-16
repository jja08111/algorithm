#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int ALPHABET=26;
int toNumber(char ch) { return ch-'A'; }

struct TrieNode {
    TrieNode* children[ALPHABET];
    // 완성된 단어의 번호
    int terminal;
    // 현재 노드까지 문자 입력시 추천 단어 리스트의 첫번째 단어의 번호를 저장한다.
    int first;
    TrieNode() : terminal(-1), first(-1) {
        memset(children,0,sizeof(children));
    }
    ~TrieNode() {
        for(int i=0;i<ALPHABET;++i)
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

int countKeys(TrieNode* trie, const char* word)
{
    TrieNode* node=trie->find(word);
    if(node==NULL || node->terminal==-1)
        return strlen(word);
    return trie->type(word,node->terminal);
}

TrieNode* readInput(int words) 
{
    // <빈도수, 문자열>
    vector<pair<int,string> > input;
    for(int i=0;i<words;++i)
    {
        char buf[11];
        int freq;
        scanf("%s %d", buf, &freq);
        // 단어들의 출현 빈도의 내림차순, 단어의 오름차순으로 정렬할 것임
        input.push_back(make_pair(-freq,buf));
    }
    sort(input.begin(), input.end());
    
    TrieNode* trie=new TrieNode();
    for(int i=0;i<input.size();++i)
        // string을 char*형으로 변환하여야 한다.
        trie->insert(input[i].second.c_str(),i);
    trie->first=-1;
    return trie;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int words, inputs;
        cin>>words>>inputs;
        TrieNode* trie=readInput(words);
        
        // 공백 수를 더한다.
        int ret=inputs-1;
        for(int i=0;i<inputs;++i)
        {
            char word[11];
            scanf("%s",word);
            ret+=countKeys(trie,word);
        }
        cout<<ret<<endl;
    }
    return 0;
}
