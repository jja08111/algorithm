# 해결 
처음에는 오른쪽으로 가는 경우와 왼쪽으로 쭉 이동하는 경우만을 생각했다.  
하지만 이 방법으로는 BABAAAAAAAAAB 와 같은 케이스를 해결할 수 없다.  
```c++
// 실패한 코드
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int DIFF='Z'-'A'+1;
const int INF=987654321;

// 목표 알파벳으로 이동하는 수 반환
int moveCount(int src, int target) {
    if(src<target)
        swap(src,target);
    return min(src-target,abs(src-target-DIFF));
}

int countControlNum(string start, const string& name) {
    int ret=0;
    for(int i=0;i<name.size();++i) {
        ret+=moveCount(int('A'),int(name[i]));
        start[i]=name[i];
        if(start==name) 
            return ret+=i;
    }
    return INF;
}

int solution(string name) {
    string pivot;
    for(int i=0;i<name.size();++i) 
        pivot+='A';
    
    int ret=INF;
    ret=countControlNum(pivot,name);
    
    char frontCh=name[0];
    name+=frontCh;
    reverse(name.begin(),name.end());
    name.pop_back();
    ret=min(ret,countControlNum(pivot,name));
    
    return ret;
}
```

그래서 어떻게 할지 고민하다가 재귀적으로 오른쪽 혹은 왼쪽을 선택해서 이동하다 완성되면 종료하는 방식으로 구현했다.  
이 방법은 계속해서 만들면 너무 많이 재귀호출하여 리미트를 걸 필요가 있었다.  
따라서 한 바퀴 돌았을 때 더이상 탐색하는 것은 무의미 하기 때문에 기저 사례에 문자열 길이보다 움직인 횟수가 초과하면 종료했다.  
```c++
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int DIFF='Z'-'A'+1;
const int INF=987654321;

// 목표 알파벳으로 이동하는 수 반환
int countConvert(int src, int target) {
    if(src<target)
        swap(src,target);
    return min(src-target,abs(src-target-DIFF));
}

// 범위를 초과하는 경우 고려
int fix(int idx, int len) {
    if(idx>=len)
        return 0;
    if(idx<0)
        return len-1;
    return idx;
}

int recur(string here, int idx, const string& name, int moveCount) {
    // 문자열이 일치하면 종료한다.
    if(here==name)
        return -1;
    // 의미없는 탐색인 경우 종료한다.
    if(moveCount>name.size())
        return INF;
    int count=countConvert(here[idx],name[idx]);
    here[idx]=name[idx];
    // 왼쪽 혹은 오른쪽으로 커서를 이동한다.
    return min(recur(here,fix(idx+1,name.size()),name,moveCount+1),
               recur(here,fix(idx-1,name.size()),name,moveCount+1))+count+1;
}

int solution(string name) {
    string start;
    for(int i=0;i<name.size();++i) 
        start+='A';
        
    int ret=recur(start,0,name,0);
    
    return ret;
}
```
