//수열 한개씩 나눠서 그 위치당 몇개의 lis가 있는지 모두 센다.
//해당 위치 다음 목록을 전부 정렬해 놓아서
//skip이내의 범위를 찾는다.
//
//if문과 오버플로를 방지하는것, 그리고 pair를 이용하것을 눈여겨 봐야한다.

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX=2000000000+1;

int n, cacheLen[501], cacheCnt[501], seq[501];

//start에서 시작하는 lis길이 반환
int getLisLen(int start)
{
    int& ret=cacheLen[start+1];
    if(ret!=-1)
        return ret;
    
    ret=1;
    for(int next=start+1;next<n;++next)
        if(start==-1 || seq[start]<seq[next])
            ret=max(ret,getLisLen(next)+1);
    
    return ret;
}

//start에서 시작하는 lis가 몇개 있는지 반환
int count(int start)
{
    if(getLisLen(start)==1)
        return 1;
    
    int& ret=cacheCnt[start+1];
    if(ret!=-1)
        return ret;
    
    ret=0;
    for(int next=start+1;next<n;++next)
    {
        if((start==-1 || seq[start]<seq[next]) && getLisLen(start)==getLisLen(next)+1)
            //오버플로를 방지한다.
            ret=min<long long>(MAX, (long long)ret+count(next));
    }
    return ret;
}

//seq[start]에서 시작하는 lis중 사전순으로 skip개 건너뛴 수열을 lis에 저장한다.
void reconstruct(int start, int skip, vector<int>& lis)
{
    if(start!=-1)
        lis.push_back(seq[start]);
    
    //pair(숫자,숫자의 위치)
    vector<pair<int,int> > followers;
    
    for(int next=start+1;next<n;++next)
        if((start==-1 || seq[start]<seq[next]) && getLisLen(start)==getLisLen(next)+1)
            followers.push_back(make_pair(seq[next],next));
    
    sort(followers.begin(),followers.end());
    
    for(int i=0;i<followers.size();++i)
    {
        int idx=followers[i].second;
        int cnt=count(idx);
        
        if(cnt<=skip)
            skip-=cnt;
        else
        {
            reconstruct(idx,skip,lis);
            break;
        }
    }
}

int main(void)
{
    int testCase; cin>>testCase;
    
    while(testCase--)
    {
        int k;
        cin>>n>>k;
        
        for(int i=0;i<n;++i)
            cin>>seq[i];
            
        memset(cacheLen,-1,sizeof(cacheLen));
        memset(cacheCnt,-1,sizeof(cacheCnt));
        
        cout<<getLisLen(-1)-1<<endl;
        
        vector<int> kthLIS;
        reconstruct(-1,k-1,kthLIS);
        
        for(int i=0;i<kthLIS.size();++i)
            cout<<kthLIS[i]<<" ";
        cout<<endl;
    }

    return 0;
}
