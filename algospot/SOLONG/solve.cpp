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
        // 첫 번째 문자가 등록 되지 않았다면 갱신
        if(first==-1)
            first=id;
        // 문자열이 끝났다면 terminal 갱신
        if(*key==0)
            terminal=id;
        else {
            int next=toNumber(*key);
            // 해당 자식 노드가 없다면 생성
            if(children[next]==NULL)
                children[next]=new TrieNode();
            // 재귀 호출
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
    // 번호가 id인 key를 타이핑 하기 위한 최소 회수 반환
    int type(const char* key, int id) {
        if(*key==0)
            return 0;
        // 이 노드에서 추천되는 문자열이 이 문자열이면 탭 누르고 종료
        if(first==id)
            return 1;
        // 아니면 다음 문자를 타이핑한다.
        int next=toNumber(*key);
        return 1+children[next]->type(key+1,id);
    }
};

int countKeys(TrieNode* trie, const char* word)
{
    TrieNode* node=trie->find(word);
    // 문자열이 사전에 없는 경우 직접 타이핑
    if(node==NULL || node->terminal==-1)
        return strlen(word);
    // 탐색하면서 타이핑할 방법을 찾는다.  
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
