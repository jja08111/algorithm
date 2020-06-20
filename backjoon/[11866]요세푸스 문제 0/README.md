# 해결 
queue를 이용하여 k번째 이전의 사람들은 뒤로 보내다가 k번째 사람이 되면 출력하고 pop하였다.
```c++
queue<int> survivor;

void josephus(int n, int k)
{
    cout<<'<';
    while(n>0)
    {
        for(int i=0;i<k-1;++i)
        {
            int tmp=survivor.front();
            survivor.pop();
            survivor.push(tmp);
        }
        cout<<survivor.front();
        survivor.pop();
        n--;
        if(n>0)
            cout<<", ";
    }
    cout<<'>'<<endl;
}
```
