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

### 2. 유클리드 알고리즘을 이용 

모든 재료중 레시피와 이미 들어간 재료의 비율이 가장 높은 재료(max)를 찾으면 더 빠르다.  
하지만 max를 찾아도 max의 비율 X와 recipe[i]를 곱했을때 정수가 나오지 않을 수 있다.  

이를 막기 위해 **모든 recipe에 대해 최대공약수를 찾아**서 모든 recipe에 곱했을때 항상 정수가 나오는 비율 X를 찾을 수 있다.  
원래 레시피를 1/b병 분량으로 만들고 그 병이 최대인 값을 구해 필요한 양을 구할 수 있다.  
따라서 아래와 같은 코드를 구현할 수 있다.  
```c++
int gcd(int p, int q)
{
    if(q==0) return p;
    return gcd(q,p%q);
}

int getCeil(int a, int b)
{
    return (a+b-1)/b;
}

vector<int> solve(const vector<int>& recipe, const vector<int>& put)
{
    int n=recipe.size();
    
    // 모든 recipe[]의 최대공약수를 구한다.
    int b=recipe[0];
    for(int i=1;i<n;++i)
        b=gcd(b,recipe[i]);
        
    // 최소한 b/b=1배는 만들어야 하므로, a의 초기 값을 b로 둔다.
    int a=b;
    
    // X를 직접 구하는 대신 getCeil(put[i]*b, recipe[i])의 최대값을 구한다.  
    // 원래의 분량을 1/b병으로 나눴을때 최대 병의 수를 구한다.  
    for(int i=0;i<n;++i)
        a=max(a,getCeil(put[i]*b,recipe[i]));
        
    // a/b배 분량을 만들면 된다.
    vector<int> ret(n);
    for(int i=0;i<n;++i)
        ret[i]=recipe[i]*a/b-put[i];
    return ret;
}
```

# 회고 
비율 X가 제일 큰 값을 찾는다는 생각은 하였으나 모든 recipe에 최대공약수를 구하는 간단한 방법을 떠올리지 못해 책을 봤다.  
```c++
// 모든 recipe[]의 최대공약수를 구한다.
int b=recipe[0];
for(int i=1;i<n;++i)
    b=gcd(b,recipe[i]);
```
