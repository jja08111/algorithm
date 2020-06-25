# 해결 
말버릇이 반복해서 나오는 것을 보면  
접미사가 k개 이상의 공통 접두사를 가지고 있을 때 그 접두사의 길이가 가장 긴 것을 구하는 문제라고 볼 수 있다.  

해결 과정은 아래와 같다.  
1. 먼저 맨버-마이어스의 접미사 알고리즘을 통해 접미사 배열을 구한다.  
```c++
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
    vector<int> group(n+1);
    for(int i=0;i<n;++i)
        group[i]=s[i];
    group[n]=-1;
    
    vector<int> perm(n);
    for(int i=0;i<n;++i)
        perm[i]=i;
    while(t<n)
    {
        Comparator compareUsing2T(group,t);
        sort(perm.begin(), perm.end(), compareUsing2T);
        
        t*=2;
        if(t>=n) break;
        
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
2. 접미사 배열은 문자열들의 사전 순서대로 정렬 되어있다.  
  이점을 이용하여 i번째부터 i+k-1번째 즉, 2개의 접미사에서 공통 접두사를 확인한다.  
3. i번째와 i+k-1번째의 공통 접두사가 없다면 0을 반환할 것이고 공통 접두사가 존재하면 그 길이를 반환한다.  
4. 얻었던 길이중 가장 긴 것을 찾아낸다.  
```c++
int commonPrefix(const string& s, int i, int j)
{
    int n=s.size();
    int ret=0;
    while(i<n && j<n && s[i]==s[j])
    {
        ret++; i++; j++;
    }
    return ret;
}

int getLongestFrequent(int k, const string& s)
{
    vector<int> a=getSuffixArray(s);
    int ret=0;
    for(int i=0;i+k<=s.size();++i)
        ret=max(ret,commonPrefix(s,a[i],a[i+k-1]));
    return ret;
}
```

# 회고 
- 접미사 배열이 정렬되어 있다는 부분을 잘 활용한 문제이다.  
이를 모르고 접미사 배열을 그룹화 할때마다 그룹의 개수를 일일이 계산하여 구하려 했으나 말도 안되는 방법이었다.  

- 접미사 배열을 만드는 코드에서 오타가 발생했었다.  
    아래 주석내의 문장 같이 작성하면 그룹화가 전혀 안된다.  
    perm[]의 순서대로 접근해야 하기 때문이다.  
```c++
vector<int> newGroup(n+1);
newGroup[n]=-1;
newGroup[perm[0]]=0;
if(compareUsing2T(perm[i-1],perm[i]))
    //invalid--> newGroup[i]=newGroup[i-1]+1;
    newGroup[perm[i]]=newGroup[perm[i-1]]+1;
```
