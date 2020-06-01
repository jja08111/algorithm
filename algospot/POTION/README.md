# 해결 
### 1. 직관적인 알고리즘 
비율이 맞을 때까지 재료를 계속 넣다가 비율이 맞으면 그만두는 방법이다.  
이 방법은 직관적이지만 시간이 오래 걸린다.  
푸는 과정은 아래와 같다.  
- i번째 재료가 원래 recipe보다 더 넣었다면 다른 재료들도 최소한 put[i]/recipe[i] 배는 넣어야 한다.  
- 따라서 j번째 자료는 recipe[j]*put[i]/recipe[i] 넣어야 하는데 **값이 소수점이라면 숫가락으로 계량이 안되니 올림하여 계산**한다.  
- 이를 반복하여 비율이 전부 맞을때 까지 반복한다.  
```c++
vector<int> getNeededPotion(const vector<int>& recipe, vector<int>& put)
{
    int n=recipe.size();
    vector<int> ret(n);
    // 각 재료를 최소한 recipe만큼은 넣어야 한다.
    for(int i=0;i<n;++i)
    {
        ret[i]=max(0,recipe[i]-put[i]);
        put[i]+=ret[i];
    }
    // 비율이 전부 맞을 때까지 재료를 계속 추가하자.
    while(true)
    {
        bool ok=true;
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
            {
                // 소수점이 있으면 올린다. 
                int required=(put[i]*recipe[j]+recipe[i]-1)/recipe[i];
                // 더 넣어야 하는가?
                if(required>put[j])
                {
                    ret[j]+=required-put[j];
                    put[j]=required;
                    ok=false;
                }
            }
        if(ok) break;
    }
    return ret;
}
```
