# 해결
처음에는 조건을 보고 헷갈렸으나 간략하게 요약하면 "**인접한 집과 색상이 달라야 한다.**" 이다.  
재귀함수를 이용하여 구현하였으며 눈여겨 볼 부분은 조건문이다.  
- 처음 칠하는 집일때
- 이전 집의 색과 현재집의 색이 다를때
위 조건이 만족할때만 현재 집의 색상을 칠하고 함수를 불러온다.
```c++
for(int color=0;color<3;++color)
        if(here==0 || previousColor!=color)
            ret=min(ret,cost[here][color]+getMinSum(here+1,color));
```
