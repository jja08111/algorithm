# 해결 
처음 시도는 맨버-마이어스의 알고리즘을 이용해 접미사 배열을 만들고 공통 접두사를 위부터 아래까지 전부 찾는 방식이었다.
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
```
하지만 이 방법은 중복되는 계산이 많아 너무 느렸다. 따라서 시간 초과가 발생했다.  

### 접미사의 특징으로 중복을 제거하자 
먼저 접미사 배열 suffix Array를 만든다. 그 후 전체 문장 s와 그 접미사 배열 앞의 위치의 접미사와 공통 접두사 길이 k를 파악한다.  
그리고 앞글자 하나씩 줄여가며 k또한 하나를 줄이면 중복으로 세는 것을 막을 수 있다.  

예를 들어 mississpi를 접미사 배열로 만든 뒤 접미사 mississipi와 그 바로 앞 접미사 배열 위치에 있는 ississpi의 공통 접두사의 길이 k를 계산한다. k=0 이다.   
그 다음 글자인 ississipi와 그 바로 앞 접미사 배열 위치에 있는 issipi의 공통 접두사를 계산하면 k=4이다.  
그 다음 글자인 ssissipid와 그 바로 앞 접미사 배열 위치에 있는 ssipi의 공통 접두사 길이는 이전에 k가 4였으니 1을 빼서 3부터 시작하는 것이다.  
바로 이 부분이 시간을 단축하는데 핵심이라고 볼 수 있다.  
접미사이기 때문에 접두사 한 글자를 빼도 다른 접미사가 되는 것을 이용하는 것이다.  

아래 코드에서 접미사의 접미사 배열에서 순위를 알기 위해 역변환 배열인 pos를 선언한 것을 눈여겨 볼 수 있다.  
```c++
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
```
