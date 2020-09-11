#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const int MAX_M=100;
int M,S;

vector<int> getMaxNum()
{
    vector<int> ret;
    int remain=S;
    for(int i=0;i<M;++i)
    {
        if(remain<=9)
        {
            ret.push_back(remain);
            remain=0;
        }
        else
        {
            ret.push_back(9);
            remain-=9;
        }
    }
    if(remain>0)
        return vector<int>();
    return ret;
}

// convert Max to Min
vector<int> convert(const vector<int>& maxNum)
{
    vector<int> ret;
    for(int idx=M-1;idx>=0;--idx)
        ret.push_back(maxNum[idx]);
    if(ret[0]==0)
    {
        if(S>0)
            ret[0]=1;
        for(int idx=1;idx<M;++idx)
            if(ret[idx]!=0)
            {
                --ret[idx];
                break;
            }
    }
    return ret;
}

int main()
{
    cin>>M>>S;
    // can't make pair
    if(M*9<S || (S==0 && M>1))
        cout<<"-1 -1"<<endl;
    else
    {
        vector<int> maxNum=getMaxNum();
        if(maxNum.empty())
        {
            cout<<"-1 -1"<<endl;
            return 0;
        }
        
        vector<int> minNum=convert(maxNum);
        
        // print minNum
        for(int i=0;i<M;++i)
            cout<<minNum[i];
        cout<<' ';
        for(int i=0;i<M;++i)
            cout<<maxNum[i];
    }
    return 0;
}
