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

int fix(int idx, int len) {
    if(idx>=len)
        return 0;
    if(idx<0)
        return len-1;
    return idx;
}

int recur(string here, int idx, const string& name, int moveCount) {
    if(here==name)
        return -1;
    if(moveCount>name.size())
        return INF;
    int count=countConvert(here[idx],name[idx]);
    here[idx]=name[idx];
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
