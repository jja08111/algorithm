# 해결 
별이 어떻게 변하고 빈 공간이 어떻게 변하는지 파악하여 해결했다.  
이때 중복되는 반복문 내부의 식들을 함수로 만들어 간략화했다.
```c++
int n;

void printStars(int line)
{
    for(int j=0;j<line;++j)
        cout<<" ";
    for(int stars=line*2;stars<(n*2)-1;++stars)
        cout<<"*";
    cout<<endl;
}

int main()
{
    cin>>n;
    
    for(int line=0;line<n;++line)
        printStars(line);
    for(int line=n-2;line>=0;--line)
        printStars(line);
    return 0;
}
```
