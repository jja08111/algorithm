#include <iostream>
#include <vector>
using namespace std;

const int MAX_BUDGET=2147483647/100;
int n,limit, price[20], prefer[20];
int c[MAX_BUDGET+1];

void init(void) {
    cin>>n>>limit;
    limit/=100;
    for(int i=0;i<n;++i) {
        cin>>price[i]>>prefer[i];
        price[i]/=100;
    }
}

int getMaxPrefer(void) {
    int ret=0;
    c[0]=0;
    for(int budget=1;budget<=limit;++budget) {
        int cand=0;
        for(int dish=0;dish<n;++dish)
            if(budget>=price[dish])
                cand=max(cand,c[(budget-price[dish])%201]+prefer[dish]);
        c[budget%201]=cand;
        ret=max(ret,cand);
    }
    return ret;
}

int main(void) {
    int testCase;
    cin>>testCase;
    while(testCase--) {
        init();
        cout<<getMaxPrefer()<<endl;
    }
}
