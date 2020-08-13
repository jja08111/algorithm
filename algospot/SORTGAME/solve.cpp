#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

const int MAX_N=8;

map<vector<int>,int> toSort;

void preCalc()
{
    vector<int> perm(MAX_N);
    for(int i=0;i<MAX_N;++i)
        perm[i]=i;
    
    queue<vector<int> > q;
    q.push(perm);
    toSort[perm]=0;
    while(!q.empty())
    {
        vector<int> here=q.front();
        q.pop();
        
        int cost=toSort[here];
        for(int i=0;i<MAX_N;++i)
            for(int j=i+2;j<=MAX_N;++j)
            {
                reverse(here.begin()+i,here.begin()+j);
                if(toSort.count(here)==0)
                {
                    q.push(here);
                    toSort[here]=cost+1;
                }
                reverse(here.begin()+i,here.begin()+j);
            }
    }
}

int solve(const vector<int>& seq)
{
    int n=seq.size();
    vector<int> compressed(MAX_N);
    for(int i=0;i<n;++i)
    {
        int smaller=0;
        for(int j=0;j<n;++j)
            if(seq[j]<seq[i])
                ++smaller;
        compressed[i]=smaller;
    }
    if(n!=MAX_N)
        for(int i=n;i<MAX_N;++i)
            compressed[i]=i;
    
    return toSort[compressed];
}

int main()
{
    int testCase;
    cin>>testCase;
    
    preCalc();
    
    while(testCase--)
    {
        int n;
        cin>>n;
        
        vector<int> seq(n);
        for(int i=0;i<n;++i)
            cin>>seq[i];
        
        cout<<solve(seq)<<endl;
    }

    return 0;
}
