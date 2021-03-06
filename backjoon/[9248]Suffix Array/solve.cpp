#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

struct Comparator {
    const vector<int>& group;
    int t;
    Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {}
    bool operator () (int a, int b) {
        if(group[a]!=group[b])
            return group[a]<group[b];
        return group[a+t]<group[b+t];
    }
};

vector<int> getSuffixArray(const string& s)
{
    int n=s.size();
    int t=1;
    vector<int> group(n+1), perm(n);
    for(int i=0;i<n;++i)
    {
        group[i]=s[i];
        perm[i]=i;
    }
    group[n]=-1;
    
    while(t<n)
    {
        Comparator compareUsing2T(group,t);
        sort(perm.begin(), perm.end(), compareUsing2T);
        
        t*=2;
        if(t>=n) break;
        
        vector<int> newGroup(n+1);
        newGroup[n]=-1;
        newGroup[perm[0]];
        for(int i=1;i<n;++i)
            if(compareUsing2T(perm[i-1],perm[i]))
                newGroup[perm[i]]=newGroup[perm[i-1]]+1;
            else
                newGroup[perm[i]]=newGroup[perm[i-1]];
        
        group=newGroup;    
    }
    return perm;
}

vector<int> getLCP(const string& s, const vector<int>& suffixArray) 
{
    int k=0, n=suffixArray.size();
    vector<int> lcp(n,0);
    vector<int> pos(s.size());
    
    //pos[접미사]=접미사 배열 위치
    for(int i=0;i<n;++i)
        pos[suffixArray[i]]=i;
    
    //전체 글자부터 전체 글자에서 길이가 1인 접미사까지 lcp를 만든다. 
    for(int i=0;i<n;++i)
    {
        //접미사 배열의 첫 번째이면 건너 뛴다.
        if(pos[i]==0) continue;
        
        //s[i...]접미사와 바로 윗 그룹 접미사의 공통 접두사의 길이 k를 구한다. 
        for(int j=suffixArray[pos[i]-1]; s[i+k]==s[j+k]; k++);
        
        lcp[pos[i]]=k;
        //1글자씩 다음 글자가 줄어드니 겹치는 부분도 1개 줄어든다.
        k=max(k-1,0);
    }
    return lcp;
}

int main()
{
    string s;
    cin>>s;
    
    vector<int> suffixArray=getSuffixArray(s);
    vector<int> lcp=getLCP(s,suffixArray);
    
    int n=suffixArray.size();
    for(int i=0;i<n;++i)
        printf("%d ",suffixArray[i]+1);
    
    cout<<endl<<"x ";
    for(int i=1;i<n;++i)
        printf("%d ",lcp[i]);

    return 0;
}
