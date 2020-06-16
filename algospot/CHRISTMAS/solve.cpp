#include <iostream>
#include <vector>
using namespace std;

const int MOD=20091101;

vector<int> getPartialSum(const vector<int>& a, int children)
{
    int n=a.size();
    vector<int> ret(n+1);
    ret[0]=0;
    for(int i=1;i<=n;++i)
        //가상의 0값을 넣었으니 a[i-1]을 더해 나간다.
        ret[i]=(ret[i-1]+a[i-1])%children;
    return ret;
}

int wayToBuy(const vector<int>& psum, int children)
{
    int ret=0;
    //psum의 값을 몇 번이나 본 적 있는지 기록한다.
    vector<long long> count(children,0);
    for(int i=0;i<psum.size();++i)
        count[psum[i]]++;
    //두 번 이상 본 적 있다면 이값 중 두 개를 선택하는 방법의 수를 더한다.
    for(int i=0;i<children;++i)
        if(count[i]>=2)
            ret=(ret+((count[i]*(count[i]-1))/2))%MOD;
    return ret;
}

int maxBuys(const vector<int>& psum, int children)
{
    //ret[i]=첫 번째 상자부터 i번째 상자까지 고려했을 때 살 수 있는 최대 횟수
    vector<int> ret(psum.size(),0);
    //prev[s]=psum[]이 s였던 마지막 위치
    vector<int> prev(children,-1);
    for(int i=0;i<psum.size();++i)
    {
        //i번째 상자를 전혀 고려하지 않음
        if(i>0)
            ret[i]=ret[i-1];
        else
            ret[i]=0;
        //psum[i]를 전에도 본 적이 있으면, prev[psum[i]]+1부터 여기까지 쭉 사본다.
        int location=prev[psum[i]];
        if(location!=-1)
            ret[i]=max(ret[i],ret[location]+1);
        //prev[]에 현재 위치를 기록한다.
        prev[psum[i]]=i;
    }
    return ret.back();
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int boxNum, children;
        scanf("%d %d",&boxNum,&children);
        vector<int> box(boxNum);
        for(int i=0;i<boxNum;++i)
            scanf("%d",&box[i]);
        
        vector<int> psum=getPartialSum(box,children);
        
        cout<<wayToBuy(psum,children)<<" "<<maxBuys(psum,children)<<endl;
    }

    return 0;
}
