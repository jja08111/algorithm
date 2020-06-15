# 해결 
비트 연산자만 이용해도 해결할 수 있을 줄 알았으나 
입출력 속도가 빠른 함수를 사용해야 했다.  
따라서 느린 cin대신 scanf를 사용해야 했고 이 때문에 string 대신 char배열로 문자열을 입력받는 것으로 구현했다.  
```c++
int main()
{
    int testCase,s=0,x;
    char operation[10];
    
    scanf("%d",&testCase);
    while(testCase--)
    {
        
        scanf("%s",operation);
        //all
        if(operation[0]=='a' && operation[1]=='l')
            s=(1<<21)-1;
        //empty
        else if(operation[0]=='e')
            s=0;
        else
        {
            scanf("%d",&x);
            //add
            if(operation[0]=='a')
                s |= (1<<x);
            //remove
            else if(operation[0]=='r')
                s &= ~(1<<x);
            //check
            else if(operation[0]=='c')
                printf("%d\n",(s&(1<<x) ? 1 : 0));
            //toggle
            else if(operation[0]=='t')
                s ^= (1<<x);
        }
    }
    return 0;
}
```
