#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MOD=20090711;

struct RNG {
    int seed,a,b;
    RNG(int _a, int _b) : a(_a), b(_b), seed(1983) {}
    int next() {
        int ret=seed;
        seed=((seed*(long long)a)+b)%MOD;
        return ret;
    }
};

int runningMedian(int n, RNG rng)
{
    //중간값과 같거나 작은 값들을 내림차순으로 저장
    //top에는 제일 큰 값이 있다.
    priority_queue<int, vector<int>, less<int> > maxHeap;
    //중간값보다 큰 값들을 오름차순으로 저장
    //top에는 제일 작은 값이 있다.
    priority_queue<int, vector<int>, greater<int> > minHeap;
    int ret=0;
    
    //반복문 불변식:
    //1.maxHeap의 크기는 minHeap의 크기와 같거나 1 더 크다.
    //2.maxHeap.top() <= minHeap.top()
    for(int cnt=1;cnt<=n;++cnt)
    {
        if(maxHeap.size()==minHeap.size())
            maxHeap.push(rng.next());
        else
            minHeap.push(rng.next());
        
        if(!minHeap.empty() && !maxHeap.empty() && 
            minHeap.top()<maxHeap.top())
        {
            int a=maxHeap.top(), b=minHeap.top();
            maxHeap.pop(); minHeap.pop();
            maxHeap.push(b);
            minHeap.push(a);
        }
        ret=(ret+maxHeap.top())%MOD;
    }
    return ret;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int n,a,b;
        cin>>n>>a>>b;
        
        cout<<runningMedian(n,RNG(a,b))<<endl;
    }
    return 0;
}
