# 해결 
### 1. linked list 이용
이 문제는 중간에 삭제되는 원소들이 존재하는데 이때 연결리스트를 사용하면 삭제시간을 O(1)만에 수행할 수 있다.  

마지막 원소에 다다른 경우 다시 처음으로 돌아오는 부분을 구현해야 한다.  
```c++
void josephus(int n, int k)
{
    list<int> soldier;
    for(int i=1;i<=n;++i)
        soldier.push_back(i);
    
    list<int>::iterator kill=soldier.begin();
    while(n>2)
    {
        kill=soldier.erase(kill);
        if(kill==soldier.end())
            kill=soldier.begin();
        n--;
        for(int i=0;i<k-1;++i)
        {
            kill++;
            if(kill==soldier.end())
                kill=soldier.begin();
        }
    }
    cout<<soldier.front()<<" "<<soldier.back()<<endl;
}
```
### 2. queue 이용
큐를 이용하면 더욱 간결하게 구현할 수 있다.  
k번째 이전의 생존자들은 뒤로 보내고 k번째 생존자는 죽이는 방식으로 구현했다.  
여기서 주의할 점은 리스트와 다르게 정렬이 안되어 있으므로 오름차순으로 출력하는 것을 생각해야 한다는 것이다.  
```c++
void josephus(queue<int>& survivor)
{
    while(n>2)
    {
        survivor.pop();
        n--;
        for(int i=0;i<k-1;++i)
        {
            int tmp=survivor.front();
            survivor.pop();
            survivor.push(tmp);
        }
    }
    
    if(survivor.front()>survivor.back())
        cout<<survivor.back()<<" "<<survivor.front()<<endl;
    else
        cout<<survivor.front()<<" "<<survivor.back()<<endl;
}
```
# 회고 
k번째 병사를 찾는 부분을 따로 for문을 만들지 않고 while문을 이용하려 했으나 코드가 너무 복잡해져서 책에 있는 코드를 보았다.  
