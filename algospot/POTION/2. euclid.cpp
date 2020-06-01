#include <iostream>
#include <vector>
using namespace std;

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

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int n;
        cin>>n;
        
        vector<int> recipe(n), put(n);
        for(int i=0;i<n;++i)
            cin>>recipe[i];
        for(int i=0;i<n;++i)
            cin>>put[i];
        
        vector<int> ret=solve(recipe,put);
        for(int i=0;i<n;++i)
            cout<<ret[i]<<" ";
        cout<<endl;
    }
    return 0;
}
