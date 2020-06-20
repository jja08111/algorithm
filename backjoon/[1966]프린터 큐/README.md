# 해결 
중요도가 높은 문서부터 출력할때, m번째 index의 출력 순서를 찾는 문제이다.  
먼저 문서를 저장할 때 문서의 index, priority를 같이 저장하였다.  
우선순위는 따로 내림차순으로 저장했다.

이후 작동 방식은 다음과 같다.  
1. 문서를 하나씩 따져 보며 우선순위가 제일 높은 문서를 만났을 때 출력하고 문서를 큐에서 삭제, 우선순위도 삭제한다. 
2. 제일 높은 우선순위가 아니면 문서를 제일 마지막 순번으로 보낸다.  
3. m번째 문서를 출력 가능하면 함수를 종료한다.  
```c++
int getOrder(priority_queue<int>& priority, queue<pair<int,int> >& document, int n, int m)
{
    int count=1;
    while(1)
    {
        //현재 문서의 우선순위가 제일 높을 때
        if(priority.top()==document.front().second)
        {
            //현재 문서가 출력 순서를 찾는 문서일 때
            if(document.front().first==m)
                return count;
            priority.pop();
            document.pop();
            count++;
        }
        else
        {   
            //문서를 제일 뒤로 보낸다.
            pair<int,int> tmp=document.front();
            document.pop();
            document.push(tmp);
        }
    }
}
```
