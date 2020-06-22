# 접미사 배열 
## 맨버-마이어스의 알고리즘 
https://blog.naver.com/PostView.nhn?blogId=kks227&logNo=221028710658   
잘 이해가 안 되신다면 d=1에서 d=2로 넘어가는 과정을 살펴봅시다.

1. 접미사 "aaba"와 "aba"를 비교한다고 쳐봅시다. 각각 그룹 번호가 1, 2였으니까 "aaba"가 이번 루프에서도 더 앞의 그룹에 속하게 됩니다.

2. 이번엔 "aba"와 "abaaba"를 비교해 봅시다. 앞의 두 글자가 같죠. 그 말인 즉슨 그룹 번호가 원래 같았단 겁니다. 둘 다 2죠. 이번엔 바로 뒤 2글자끼리 비교합니다. "a"는 0번 그룹, "aaba"는 1번 그룹에 속해 있었기에 "abaaba"가 이번 루프에서 더 뒤의 그룹에 속하게 됩니다.

3. 마지막으로 "aaba"와 "aabaaba"는 이런 식으로 2번 비교할 시 그룹 번호가 계속 똑같아서 이번 루프에서도 같은 그룹에 속합니다.  

[출처] 접미사 배열(Suffix Array) (수정: 2018-03-03)|작성자 라이

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
```
위 코드에서 2t 글자 기준으로 그룹이 일치하면 해당 접미사의 t만큼 뒤에 있는 접미사 즉, abaaa이고 t가 1이면 baaa를 비교하는 방식으로 나아가는 것이 핵심이다.  
