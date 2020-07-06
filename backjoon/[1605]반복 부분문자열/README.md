# 해결 
이 문제를 해결하는 방법은 여러가지가 있지만 나는 접미사 배열을 생성하고 이를 활용하는 방법을 택했다.  
### 접미사 배열 형성 
접미사 배열은 [맨버-마이어스의 알고리즘](https://github.com/jja08111/algorithm/tree/master/algospot/20%20%EB%AC%B8%EC%9E%90%EC%97%B4/5%20%EC%A0%91%EB%AF%B8%EC%82%AC%20%EB%B0%B0%EC%97%B4)을
이용하여 형성했다.
```c++
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
```

### 가장 긴 반복 부분문자열 찾기 
이제 문자열 내에서 두 번 이상 나타나는 반복 부분문자열의 길이를 구하면 된다.  
접미사 배열은 사전 순으로 정렬되어 있어 접미사 배열에서 접두사가 겹치는 접미사들이 인접해 위치한 것을 이용할 수 있다.  
겹치는 부분 overlap은 다음 문자열, 즉 접미사 한 글자를 없앤 다음 접미사는 overlap-1일 것이다.  

전체 문자열에서 하나씩 줄인 접미사들로 접근하니 suffixArray의 역함수를 만들어 이용하였다.  
```c++
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
```
