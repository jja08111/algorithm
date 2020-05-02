#include <iostream>
#include <cstring>
using namespace std;

const int MAX_N=15;

string word[MAX_N+1];
int k;
int overlap[MAX_N+1][MAX_N+1], cache[MAX_N][(1<<MAX_N)+1];

/*직접 만든 부분수열일 경우 참을 반환하는 함수 오류가 있다
//here앞에 있는 문자가 here문자에 포함되는 경우를 해결하지 못한다.
bool isSubstring(int index)
{
    string here=word[index];
    for(int i=0;i<index;++i)
        if(word[i].find(here)!=string::npos || here.find(word[i])!=string::npos)
            return true;
    return false;
}
*/

int getOverlapSize(const string& a, const string& b)
{
    int len;
    for(len=min(a.size(),b.size());len>0;len--)
        //a의 오른쪽 부분과 b의 왼쪽 부분을 비교하며 일치하면 일치하는 크기를 반환
        if(a.substr(a.size()-len)==b.substr(0,len))
            return len;
    return 0;
}

void init(void)
{
    cin>>k;
    memset(cache,-1,sizeof(cache));
    
    for(int i=0;i<k;++i)
        cin>>word[i];

    while(true) 
    {
		bool removed=false;
		for (int i=0;i<k && !removed;i++) 
			for (int j=0;j<k;j++) 
			    //j문자가 i문자에 속할 경우
				if (i!=j && word[i].find(word[j])!=-1) 
				{
					//맨끝의 문자를 j에 넣는다.
					word[j]=word[k-1];
					//범위를 1줄인다.
					k--;
					removed=true;
				}
		if (!removed) break;
	}
    word[k]="";
    
    for(int i=0;i<=k;++i)
        for(int j=0;j<=k;++j)
            overlap[i][j]=getOverlapSize(word[i],word[j]);
}

int restore(int last, int used)
{
    if(used==(1<<k)-1)
        return 0;
    
    int& ret=cache[last][used];
    if(ret!=-1)
        return ret;
    
    ret=0;
    for(int next=0;next<k;++next)
        if((used&(1<<next))==0)
        {
            //겹치는 부분이 최대가 되도록 한다.
            int cand=overlap[last][next]+restore(next,used+(1<<next));
            ret=max(ret,cand);
        }
        
    return ret;
}

string reconstruct(int last, int used)
{
    if(used==(1<<k)-1)
        return "";
    
    for(int next=0;next<k;++next)
    {
        //next가 이미 사용된 경우는 예외
        if(used&(1<<next))
            continue;
        
        //next를 사용했을때 최적해인 경우 next를 사용한다.
        int ifUsed=restore(next,used+(1<<next))+overlap[last][next];
        
        if(restore(last,used)==ifUsed)
            return (word[next].substr(overlap[last][next]) + reconstruct(next,used+(1<<next)));
    }
    
    return "error!";
}

int main(void)
{
    int testCase; cin>>testCase;
    
    while(testCase--)
    {
        init();
        
        cout<<reconstruct(k,0)<<endl;
    }
}
