# 접미사 배열 
## 맨버-마이어스의 알고리즘 

이 알고리즘을 요약하면 다음과 같다.  
1. **접미사들의 첫 번째 글자를 기준으로 같은 글자면 같은 그룹에, 다른 글자면 다른 그룹에 배정한다.**  
    이때 길이가 0인 접미사를 -1로 저장해 놓아 이용한다.  
2. **접미사 배열을 0부터 n-1까지 만든다.**  
    여기서 문자열을 저장하는 것이 아니라 접미사가 원래 문자열에서 시작하는 위치를 저장한다.  
    그룹의 인덱스 또한 마찬가지다.  
3. 접미사 배열을 정렬하는데 현재 t=1이다. **즉, 두 번째 글자를 기준으로 정렬하는 것이다.**  
    정렬시 첫 번째 글자가 다르면 그대로 이용한다.  
    다르면 t번째 글자, 즉 두 번째 글자로 시작하는 접미사의 그룹을 이용하여 정렬한다.  
    - **이 부분이 굉장히 중요한데 이전에 계산해 두었던 그룹들을 이용하는 것이다.**    
      첫 글자를 정렬해 두었으면 그 다음 첫 글자를, 네 글자를 정렬해 두었으면 바로 그 다음 네 글자를 이용할 수 있는 것이다.  
      **이러한 이유 때문에 속도가 빠를 수 있는 것이다.**
4. 정렬 후 2t가 n을 넘는다면 접미사 배열을 완성한 것이니 반복문을 빠져 나온다.
5. 넘지 않는다면 그룹화를 해야 한다. 접미사들이 정렬 되어있으니 비교를 통해 제일 처음 접미사보다 크다면 다음 그룹으로 번호를 선정한다.  

짧게 정리한다고 해봤는데 그래도 길다.  
그만큼 간단하지 않은 알고리즘인 것 같다.
    

```c++
struct Comparator {
    const vector<int>& group;
    int t;
    Comparator(const vector<int>& _group, int _t): group(_group), t(_t) {
        group=_group; t=_t;
    }
    bool operator () (int a, int b) {
        if(group[a]!=group[b])
            return group[a]<group[b];
        return group[a+t]<group[b+t];
    }
};

vector<int> getSuffixArray(const vector<int>& s)
{
    int n=s.size();
    int t=1;
    
    //첫 번째 글자를 기준으로 그룹화
    vector<int> group(n+1);
    for(int i=0;i<n;++i)
        group[i]=s[i];
    group[n]=-1;
    
    //접미사 배열이 될 값
    vector<int> perm(n);
    for(int i=0;i<n;++i)
        perm[i]=i;
    
    while(t<n)
    {
        Comparator compareUsing2T(group,t);
        sort(perm.begin(), perm.end(), compareUsing2T);
        
        //2t글자가 n을 넘는다면 접미사 배열 완성
        //구조체에는 아직 t*=2를 대입하지 않았다!!!
        t*=2;
        if(t>=n) break;
        
        vector<int> newGroup(n+1);
        newGroup[n]=-1;
        newGroup[perm[0]]=0;
        for(int i=1;i<n;++i)
            if(compareUsing2T(perm[i-1],perm[i]))
                newGroup[i]=newGroup[i-1]+1;
            else
                newGroup[i]=newGroup[i-1];
        group=newGroup;
    }
    return perm;
}
```


# 참고 
- https://blog.naver.com/PostView.nhn?blogId=kks227&logNo=221028710658   
