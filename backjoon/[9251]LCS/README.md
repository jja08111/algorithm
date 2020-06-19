# 해결 
완전탐색부터 시작하자는 생각을 가지고 접근했다.  
문자열 A와 문자열 B에서 같은 문자를 만나는 경우 수열의 길이를 하나씩 늘리며 나아가는 방식으로 만들었다.  
만약 A와 B의 문자가 다른 경우 수열에 문자를 추가하지 않고 다음 인덱스로 넘어 가도록 구현했다.  
```c++
int LSC(int indexA, int indexB)
{
    int& ret=cache[indexA][indexB];
    if(ret!=-1)
        return ret;
    
    ret=0;
    int nextB;
    //strA와 같은 문자가 strB에 있는 경우
    for(nextB=indexB;nextB<lenB;++nextB)
        if(strA[indexA]==strB[nextB])
            ret=max(ret,LSC(indexA+1,nextB+1)+1);
    
    //strA와 같은 문자가 strB에 없는 경우
    if(indexA<lenA && nextB==lenB)
        ret=max(ret,LSC(indexA+1,indexB));
    
    return ret;
}
```

### 더 빠른 재귀함수
하지만 위의 구현은 반복문에서 의미 없는 낭비가 심하다.  
이를 방지하기 위해서는 현재 인덱스에서 두 문자가 같지 않을 경우 A인덱스를 넘기거나, B인덱스를 넘긴 결과 중 더 큰 값을 반환하도록 하면 된다.  
```c++
int LSC(int indexA, int indexB)
{
    int& ret=cache[indexA][indexB];
    if(ret!=-1)
        return ret;
    //범위를 벗어나면 종료한다.
    if(indexA>=lenA || indexB>=lenB)
        return 0;
    
    ret=0;
    //문자가 일치하는 경우
    if(strA[indexA]==strB[indexB])
        return ret=LSC(indexA+1,indexB+1)+1;
    
    //문자가 일치하지 않는 경우
    return ret=max(LSC(indexA+1,indexB),LSC(indexA,indexB+1));
}
```
이렇게 수정하고 속도가 약 500ms에서 8ms로 엄청나게 향상되었다.  
