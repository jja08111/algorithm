#include <iostream>
#include <vector>
using namespace std;

const int MOD=20091101;

int boxNum, children;

vector<int> partialSum(const vector<int>& a)
{
    int n=a.size();
    vector<int> ret(n);
    ret[0]=a[0];
    for(int i=1;i<n;++i)
        ret[i]=ret[i-1]+a[i];
    return ret;
}

int rangeSum(const vector<int>& psum, int a, int b)
{
    if(a==0) return psum[b];
    return psum[b]-psum[a-1];
}

int solve1(const vector<int>& psum)
{
    int ret=0;
    for(int a=0;a<boxNum;++a)
        for(int b=a;b<boxNum;++b)
        {
            int sum=rangeSum(psum,a,b);
            if(sum%children==0)
                ret=(ret+1)%MOD;
        }
    return ret;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>boxNum>>children;
        vector<int> box(boxNum);
        for(int i=0;i<boxNum;++i)
            cin>>box[i];
        
        vector<int> psum=partialSum(box);
        
        cout<<solve1(psum)<<" ";
    }

    return 0;
}
