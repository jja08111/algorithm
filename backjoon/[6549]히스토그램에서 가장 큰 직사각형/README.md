# 해결 
이 문제는 분할정복을 통해 재귀적으로 해결할 수 있으나 더욱 빠른 방법인 스택을 이용한 해결방법이 있다.  

이 방법은 0번부터 가장 오른쪽 히스토그램까지 하나씩 추가하며 휩쓸어 나아가는 방식이다.  
오른쪽으로 나아갈때 왼쪽에 남아있는 히스토그램의 높이가 낮아지게 되면 그 이전 히스토그램의 높이를 기준으로 하는 넓이는 현재 히스토그램에 막혀 최대값이 한계에 도달했다.  
그렇기에 이전 히스토그램의 너비를 구해 넓이를 구하고 의미없게 된 이전 히스토그램을 제거한다.  
마지막에는 높이 -1의 가상의 히스토그램을 추가해 남아있던 모든 히스토그램의 최대 넓이를 구한다.  

위와 같은 진행이 가능한 이유는 오른쪽으로 갈수록 히스토그램의 높이가 커지기 때문이다.  
그리고 i번째 히스토그램 왼쪽에는 자신보다 낮은 높이의 히스토그램만 남아있어 너비를 구할 때 왼쪽 지점을 알 수 있다.  

너비를 구할 때 남아있는 판자 중 가장 오른쪽에 있는 판자를 통해 왼쪽 너비를 구하기 때문에 스택에 넣으면 적절하다.  
유의할 점은 결과 값이 오버플로가 발생할 수 있는 부분이다.  
```c++
long long getMaxArea()
{
    stack<int> remaining;
    h.push_back(-1);
    long long int ret=0;
    for(int i=0;i<h.size();++i)
    {
        while(!remaining.empty() && h[remaining.top()]>=h[i])
        {
            int j=remaining.top();
            remaining.pop();
            int width=-1;
            
            if(remaining.empty())
                width=i;
            else
                width=(i-remaining.top()-1);
            ret=max(ret,(long long)width*h[j]);
        }
        remaining.push(i);
    }
    return ret;
}
```
