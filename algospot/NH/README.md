# 해결 
모든 문자열을 만드는 재귀함수를 작성한 뒤, 메모이제이션을 통해 해결할 수 없다. 왜냐하면 문자열 전체를 넘겨받는 함수에 메모이제이션을 적용할 수 없기 때문이다.  
그렇다면 이전 부분에 대해 넘겨받는 정보를 최소화 해야 한다. 그 방법은 아호-코라식 알고리즘에 있다.  

### 아호-코라식을 이용한 해결 
입력된 문자열들은 IDS의 패턴이다. 이 문자열은 만들어야 하는 문자열에 절대 포함되어서는 안된다.  
IDS패턴들을 담은 트라이를 만든 뒤, 동적 계획법을 통해 한 글자씩 추가하며 남은 길이와 현재 노드를 넘겨 가능한 문자열 개수를 구한다.  
이때 다음 노드를 어떻게 찾을까? 

현재 트라이 노드에서 문자를 추가했는데 해당 문자 간선이 없는 경우 아호-코라식 방식으로 fail을 찾아간다.  
찾아가다 보면 결국 루트에 도달하거나 접미사 노드에 도달하였을 것이다.  
즉, 현재 노드에서 a~z 중 한 글자를 넣게 되면 다음 노드는 어떤 노드인지 저장하는 것이다.  
이런식으로 next[]를 채운다.  
```c++
// 해당 노드에서 a~z 중 한 개의 문자가 추가될 경우 
// 이동하게 될 노드를 찾는다.
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
```
next를 채우면 동적 계획법을 통한 해결은 간단하다.  
트라이 내부를 돌다가 output에 글자가 등록되어 있는 경우 0을 반환하며, IDS에 등록된 문자열을 만나지 않고 문자열을 완성시키면 1을 반환시키며 재귀하면 된다.
```c++
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
```
