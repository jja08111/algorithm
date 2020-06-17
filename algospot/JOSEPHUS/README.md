# 해결 
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
# 회고 
k번째 병사를 찾는 부분을 따로 for문을 만들지 않고 while문을 이용하려 했으나 코드가 너무 복잡해져서 책에 있는 코드를 보았다.  
