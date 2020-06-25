#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

struct Comparator {
    const vector<int>& group;
    int t;
    Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {}
    bool operator () (int a, int b) {
        if(group[a]!=group[b])
            return group[a]<group[b];
        return group[a+t]<group[b+t];
    }
};

inline int index(char a)
{
    return (int)(a-'a');
}

int getLongestHabit(const string& s, const int k)
{
    int n=s.size();
    int t=1;
    vector<int> group(n+1);
    vector<int> groupSize(index('z')+1, 0);
    for(int i=0;i<n;++i)
    {
        group[i]=s[i];
        groupSize[index(s[i])]++;
    }
    group[n]=-1;
    
    vector<int> perm(n);
    for(int i=0;i<n;++i)
        perm[i]=i;
    
    
    
    while(t<n)
    {
        Comparator compareUsing2T(group,t);
        sort(perm.begin(), perm.end(), compareUsing2T);
        
        t*=2;
        if(t>=n) break;
        
        vector<int> newGroup(n+1);
        newGroup[n]=-1;
        newGroup[perm[0]]=0;
        for(int i=1;i<n;++i)
            if(compareUsing2T(perm[i-1], perm[i]))
                newGroup[i]=newGroup[i-1]+1;
            else
            {
                newGroup[i]=newGroup[i-1];
                
            }
        group=newGroup;
    }
    return 0;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        int k;
        string s;
        cin>>k>>s;
        
        cout<<getLongestHabit(s,k)<<endl;
    }

    return 0;
}
