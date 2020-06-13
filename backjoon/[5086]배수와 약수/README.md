# 해결
나머지 연산자를 이용하여 해결했다.  
```c++
int main()
{
    int a,b;
    
    while(true)
    {
        cin>>a>>b;
        if(a==0 && b==0)
            break;
        
        if(b%a==0)
            cout<<"factor"<<endl;
        else if(a%b==0)
            cout<<"multiple"<<endl;
        else
            cout<<"neither"<<endl;
    }

    return 0;
}
```
# 회고 
multiple을 muliple이라고 잘못 적어 오류가 발생했다.  
항상 상수의 경우 오타에 주의해야 한다.
