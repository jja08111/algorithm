# 해결 
검색시 자동 추천을 보면 트라이가 떠오른다.  
트라이는 원하는 원소를 빠르게 찾을 수 있으나 메모리가 크게 낭비되는 자료 구조이다.  
트라이의 객체는 자손 노드를 가리키는 포인터 목록과, 이 노드가 종료 노드인지를 나타내는 값을 가지고 있다.  

이 문제에서 빈도수가 높거나, 같다면 사전순으로 단어들을 추천해 주는데 이 추천 단어가 제일 첫 번째에 와야지 탭을 눌러 선택할 수 있다.  
따라서 입력값들을 빈도수, 사전순으로 정렬하여 순서대로 객체에 추가하면 탭하는 과정을 쉽게 구현할 수 있다.  
```c++
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
```
----------------------
삽입하는 함수는 첫 번째 단어가 등록되어 있지 않았을 때 바로 현재 문자열의 id를 넣는다. 전처리 과정 중 정렬되었기 때문에 문제없이 first가 갱신된다.  
그 후 문자열이 종료되면 terminal에 id를 등록한다. 문자열이 끝나지 않았다면 다음 문자로 넘어간다.  

타이핑하는 회수를 찾는 함수는 현재 노드에서 추천되는 문자열(first)가 현재 문자열 id와 동일하다면 탭을 눌러 종료하며 아니면 다음 문자를 타이핑한다.  
```c++
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
```
------------------------
사전을 나타내는 trie가 주어질 때, 단어 word를 타이핑 하는 수를 계산하는 함수는 문자열이 사전에 없는 경우를 유의하여 작성해야 한다.  
```c++
int countKeys(TrieNode* trie, const char* word)
{
    TrieNode* node=trie->find(word);
    // 문자열이 사전에 없는 경우 직접 타이핑
    if(node==NULL || node->terminal==-1)
        return strlen(word);
    // 탐색하면서 타이핑할 방법을 찾는다.  
    return trie->type(word,node->terminal);
}
```
