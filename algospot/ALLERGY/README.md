# 해결 
처음에는 m 종류의 음식이 있으니, 2^m가지의 모든 경우의 수를 만들어 보는 방법을 떠올릴 것이다.  
여기서 최적해보다 현재 만든 음식 가짓수가 크면 중단하는 가지치기를 적용할 수 있다.  
하지만 이 방법은 너무 느리다.  
### 1. 못먹는 사람을 우선으로
첫번째 아이디어는 못먹는 사람을 우선적으로 처리하는 방법이다.  
현재 못먹는 사람이 나오면 그 사람이 먹을 수 있는 음식을 만들어 해결해 나가는 것이다.  
이 방법은 이전 방법이 이미 먹는것이 있는 사람이 먹을 수 있는 음식을 만들어 낼때 그러한 중복을 없애 훨씬 빠르다.  
```c++
void search(vector<int>& edible, int chosen)
{
    if(chosen>=best)
        return;
    //아직 먹을 음식이 없는 친구를 찾음
    int first=0;
    while(first<friendNum && edible[first]>0)
        ++first;
    //기저사례 : 전부 먹을 음식이 있는 경우
    if(first==friendNum)
    {
        best=chosen;
        return;
    }
    //first친구가 먹을 수 있는 음식을 찾음
    for(int i=0;i<canEat[first].size();++i)
    {
        int food=canEat[first][i];
        for(int j=0;j<eaters[food].size();++j)
            edible[eaters[food][j]]++;
        search(edible,chosen+1);
        for(int j=0;j<eaters[food].size();++j)
            edible[eaters[food][j]]--;
    }
}
```
### 2. 비트 연산자 이용
집합들을 비트 연산자로 바꿔서 코딩하면 더욱 빠르다.  
단, 범위를 long long 으로 해주어야 벗어나지 않아 제대로 계산할 수 있다.  
최적화 버전.cpp을 참고하기 바란다.  
### 3. 먹을 수 있는 음식의 종류가 적은 친구부터 찾자
먹을 수 있는 음식의 종류가 적은 친구는 먹을 수 있는 음식을 얻기 어렵다.  
따라서 이 친구부터 챙겨주자.  
```c++
int minimum(long long int edible)
{
    int minFriend,minCount=50;
    for(int i=0;i<n;++i)
        if(~edible&(1LL<<i))
        {
            int count=__builtin_popcount(canEat[i]);
            if(count<minCount)
            {
                minCount=count;
                minFriend=i;
            }
        }
    return minFriend;
}
```

# 회고
- 비트 연산자를 이용할때 범위를 벗어나는 경우 (1<<num)과 같은 부분을 (1LL<<num)으로 유의해서 작성해야 한다.
- 3번의 경우 비트연산자를 이용하지 않는 것이 더 빠르다.  
