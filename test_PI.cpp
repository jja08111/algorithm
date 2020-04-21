#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF=987654321;

string pi;
int cache[10002];

int classify(int start, int end)
{
    string str=pi.substr(start,end-start+1);
    
    //level : 1 
    if(str==string(str.size(),str[0]))
        return 1;
    
    //등차수열인지 확인한다.
    bool progressive=true;
    
    for(int i=0;i<str.size()-1;++i)
        //첫번째와 두번째 인덱스의 차이로만 비교하는 것이 인상적이다.
        if(str[i+1]-str[i] != str[1]-str[0])
            progressive=false;
    
    //등차수열인데 차이가 1인경우이다.
    if(progressive && abs(str[1]-str[0])==1)
        return 2;
    
    //숫자가 번갈아 가며 등장하는지 확인한다.
    bool alternating=true;
    
    for(int i=0;i<str.size();++i)
        //나머지 연산자를 이용하여 확인하는것 또한 인상적이다.
        if(str[i]!=str[i%2])
            alternating=false;
    
    if(alternating) return 4;
    if(progressive) return 5;
    
    return 10;
}

/* 직접 분류하는 함수를 만들려고 했으나 실패
int 11classify(int start, int end)
{
    for(int idx=start;idx<end-1;++idx)
    {    
        if(pi[idx]==pi[idx+1])
        {
            if(idx==end-2)
                return 1;
        }
        else
            break;
    }
    
    //여기서 부터 잘못 되었따.
    int diff=pi[start+1]-pi[start];
    int level=(abs(diff)>1) ? 5 : 2;
    //int delta=diff/abs(diff);
    
    for(int idx=start;idx<end-1;++idx)
        if(pi[idx]+diff!=pi[idx+1])
        {
            if(pi[idx]+(diff*-1)==pi[idx+1])
                level=4;
            else
                return 10;
        }
    
    return level;
}
*/

int getMinLevel(int start)
{
    if(start==pi.size())
        return 0;
    
    int& ret=cache[start];
    if(ret!=-1)
        return ret;
    
    ret=INF;
    for(int piece=3;piece<=5;++piece)
        if(start+piece<=pi.size())
            ret=min(ret, classify(start, start+piece-1)+getMinLevel(start+piece));
    
    return ret;
}

int main(void)
{
    int testCase;
    
    cin>>testCase;
    
    while(testCase--)
    {
        cin>>pi;
        
        memset(cache,-1,sizeof(cache));
        
        cout<<getMinLevel(0)<<endl;
    }
    
    return 0;
}
