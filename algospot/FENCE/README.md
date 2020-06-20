# 해결 
왼쪽부터 오른쪽까지 휩쓸듯이 처리하는 스위핑 알고리즘을 이용하면 굉장히 효율적으로 해결할 수 있다.  
주요 방식은 한 칸씩 오른쪽으로 넘어가다가 펜스의 높이가 낮아진 경우 이전 펜스의 높이와 가로넓이를 구해서 해당 낱개의 펜스를 높이로하는 넓이를 구한다.  
이를 계속 반복하며 최대 넓이를 찾는 것이다. 구현을 간단하게 하기 위해서 마지막에 가상의 0 높이의 펜스를 추가 할 수 있다.  
높이를 구한 펜스는 제거한다. 

여기서 생각나는 자료구조가 있는데 바로 스택이다.  
마지막에 넣는 펜스를 너비를 구할 때 사용하므로 후입선출인 스택을 이용하면 쉽게 구현 할 수 있다.
```c++
int solveStack()
{
    stack<int> remaining;
    h.push_back(0);
    int ret=0;
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
            ret=max(ret,h[j]*width);
        }
        remaining.push(i);
    }
    return ret;
}
```
