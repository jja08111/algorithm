#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Comparator {
    const vector<int>& group;
    int t;
    Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {}
    bool operator () (int a, int b) {
        if(group[a] != group[b])
            return group[a]<group[b];
        return group[a+t]<group[b+t];
    }
};

vector<int> getSuffixArray(const string& s)
{
    int n=s.size();
    int t=1;
    
    // 첫 글자를 기준으로 그룹화 한다.
    vector<int> group(n+1);
    for(int i=0;i<n;++i)
        group[i]=s[i];
    group[n]=-1;
    
    // 0부터 n-1까지 접미사 배열이 될 값을 생성한다.  
    vector<int> perm(n);
    for(int i=0;i<n;++i)
        perm[i]=i;
    
    while(t<n)
    {
        // 2t글자를 기준으로 perm을 정렬한다.
        Comparator compareUsing2T(group, t);
        sort(perm.begin(), perm.end(), compareUsing2T);
        
        t*=2;
        if(t>=n)
            break;
        
        // 정렬된 2t글자를 기준으로 다시 그룹화 한다.
        vector<int> newGroup(n+1);
        newGroup[n]=-1;
        newGroup[perm[0]]=0;
        for(int i=1;i<n;++i)
            if(compareUsing2T(perm[i-1],perm[i]))
                newGroup[perm[i]]=newGroup[perm[i-1]]+1;
            else
                newGroup[perm[i]]=newGroup[perm[i-1]];
        
        group=newGroup;
    }
    return perm;
}

int getLongestPreffix(const string& s, const vector<int>& suffixArr)
{
    vector<int> pos(s.size());
    int overlap=0, n=suffixArr.size(), ret=0;
    
    // 전체 문자열 부터 0글자인 문자열 까지 순서대로 방문하므로 
    // suffixArr의 역함수를 만들어 쉽게 접근한다.
    for(int i=0;i<n;++i)
    {
        pos[suffixArr[i]]=i;
        //cout<<i<<':'<< &s[suffixArr[i]] <<endl;
    }
    
    for(int i=0;i<n;i++)
    {
        // 맨 위의 접미사 배열일때
        if(pos[i]==0) continue;
        
        // 현재의 접미사와 바로 위의 접미사의 겹치는 접두사 길이를 구한다.
        for(int j=suffixArr[pos[i]-1]; s[i+overlap]==s[j+overlap]; overlap++);
        
        ret=max(ret,overlap);
        // 겹치는 길이를 1 줄인다.
        overlap=max(overlap-1,0);
    }
    return ret;
}

int main()
{
    int n;
    string s;
    cin>>n>>s;
    
    cout<<getLongestPreffix(s,getSuffixArray(s))<<endl;

    return 0;
}
