# 해결 
우선순위가 높은 값들 순으로 저장하는 priority_queue로 해결했다.  
이때 오름차순으로 정렬하여야 하니 greater<int>를 이용했다.  
```c++
int main()
{
    int n;
    cin>>n;
    priority_queue<int, vector<int>, greater<int> > pq;
    while(n--)
    {
        int x;
        scanf("%d",&x);
        
        if(x==0)
        {
            if(pq.empty())
                printf("0 \n");
            else
            {
                printf("%d \n",pq.top());
                pq.pop();
            }
        }
        else
            pq.push(x);
    }
    return 0;
}
```
