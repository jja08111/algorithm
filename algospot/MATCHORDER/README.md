# 해결
### 1. 동적계획법
한국팀의 출전 순서를 맨 앞에서부터 한명씩 정해간다.  
모든 방법을 탐색해보고 한국 선수를 추가했는지의 여부인 taken이라는 불린값 배열을 받는 부분 문제를 만들수 있다.  
하지만 이방법은 100명의 선수로 구성되있다면 속도가 너무 느리다.  

### 2. 탐욕법
직관적으로 아래와 같이 생각할 수 있다.  
- 한국팀의 모든 선수를 이기는 러시아 선수가 있다면 한국팀의 가장 낮은 레이팅의 선수를 내보낸다.
- 이길 수 있는 선수라면 그 중 가장 레이팅이 낮은 한국선수를 내보낸다.

multiset을 이용한 방법이 인상적이다.
- rating초기화시 바로 정렬이 된다.
- rbegin()을 이용해 가장 높은 선수를 쉽게 접근한다.
- begin()을 이용해 가장 낮은 선수 또한 쉽게 알 수 있다.
- lower_bound를 이용해 russian[rus]와 같거나 큰것중 제일 작은 것에 쉽게 접근한다.
```c++
int order(const vector<int>& russian, const vector<int>& korean)
{
    int n=russian.size(), wins=0;
    
    //아직 남아 있는 선수들의 레이팅
    multiset<int> ratings(korean.begin(),korean.end());
    for(int rus=0;rus<n;++rus)
    {
        //가장 레이팅이 높은 한국 선수가 이길 수 없는 경우
        //가장 레이팅이 낮은 선수와 경기시킨다.
        if(*ratings.rbegin() < russian[rus])
            ratings.erase(ratings.begin());
        //이 외의 경우 이길 수 있는 선수 중 가장 레이팅이 낮은 선수와 경기시킨다.
        else
        {
            ratings.erase(ratings.lower_bound(russian[rus]));
            ++wins;
        }
    }
    return wins;
}
```
