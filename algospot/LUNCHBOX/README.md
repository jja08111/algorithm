# 해결
직접 손으로 풀다보면 전자레인지에 데워지는 순서는 상관이 없고 먹는 시간의 순서가 중요하단걸 알 수 있다.  
즉, 오래걸리는 도시락 부터 먹어야 한다는 것이다.  
따라서 먹는 시간을 기준으로 내림차순으로 정렬하여 마지막에 가장 빠르게 먹을 수 있는 음식을 배치한다.  

나는 이전까지의 먹는데 걸리는 시간에서 데우는 시간을 뺀것과 현재 먹는데 걸리는 시간을 비교하여 더 큰 값을 결과에 더해주었다. 
```c++
//first : 먹는데 걸리는 시간(음수로 되어 있음), second : 데우는 시간
for(int i=1;i<n;++i)
{
    heatingTime+=food[i].second;
    //데웠던 시간을 빼준다.
    remainingEat+=food[i].second;
    //음수이기 때문에 min을 찾는다
    remainingEat=min(remainingEat,food[i].first);
}
```

하지만 교재에서는 어차피 먹는데 시간이 엄청 클 경우, 데우는 시간을 아무리 더해도 전자보다는 작다는 점을 이용하였다. 
계속해서 먹는데 걸리는 시간에서 데우는 시간을 빼지 않는 것이다.   
그래서 코드도 깔끔하고 직관적이다.
```c++
//first : 먹는데 걸리는 시간(음수로 되어 있음), second : first의 index
for(int i=0;i<n;++i)
{
    int box=order[i].second;
    beginEat+=heat[box];
    ret=max(ret,beginEat+eat[box]);
}
```
