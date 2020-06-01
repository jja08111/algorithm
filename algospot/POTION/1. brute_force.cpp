#include <iostream>
#include <vector>
using namespace std;

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
    // 비율이 전부 맞을 떄까지 재료를 계속 추가하자.
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
        
        vector<int> ret=getNeededPotion(recipe,put);
        for(int i=0;i<n;++i)
            cout<<ret[i]<<" ";
        cout<<endl;
    }
    return 0;
}
