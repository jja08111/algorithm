#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n, limit;
int volume[100], need[100];
int cache[1001][100];
string name[100];

void init(void)
{
    cin>>n>>capacity;
    
    memset(cache,-1,sizeof(cache));
    
    for(int i=0;i<n;++i)
        cin>>name[i]>>volume[i]>>need[i];
}

//item을 선택하거나 하지 않는 2가지 방법을 이용해 최대 '절박도'합을 반환
int pack(int capacity, int item)
{
    if(item==n)
        return 0;
    
    int& ret=cache[capacity][item];
    if(ret!=-1)
        return ret;
    
    ret=pack(capacity,item+1);
    if(capacity>=volume[item])
        ret=max(ret, pack(capacity-volume[item], item+1)+need[item]);
    
    return ret;
}

void reconstruct(int capacity, int item, vector<string>& picked)
{
    if(item==n)
        return;
    
    if(pack(capacity, item)==pack(capacity, item+1))
        reconstruct(capacity,item+1,picked);
    else
    {
        picked.push_back(name[item]);
        reconstruct(capacity-volume[item],item+1,picked);
    }
}

/*
// 직접 만드려고 했던 코드이지만 반복문 부분에서 연속적으로 선택되며
// 현재 아이템을 포함하지만 용량에서는 제외하는 오류가 있다.
int getMaxNecessity(int start, int capacity)
{
    int& ret=cache[start+1][capacity];
    if(ret!=-1)
        return ret;
    
    ret=0;
    int bestNext=-1;
    for(int next=start+1;next<n;++next)
        if(start==-1 || pack[next].first<=capacity)
        {
            int cand=getMaxNecessity(next, capacity-pack[next].first)+pack[next].second;
            if(cand>ret)
            {
                ret=cand;
                bestNext=next;
            }
        }
    choices[start+1]=bestNext;
    return ret;
}

void reconstruct(int start, vector<string>& retPack)
{
    if(start!=-1) 
        retPack.push_back(name[start]);
    
    int next=choices[start+1];
    
    if(next!=-1)
        reconstruct(next,retPack);
}
*/

int main(void)
{
    int testCase; cin>>testCase;
    
    while(testCase--)
    {
        init();
        
        cout<<pack(limit,0)<<" ";
        
        vector<string> picked;
        
        reconstruct(limit,0,picked);
        
        int len=picked.size();
        
        cout<<len<<endl;
        for(int i=0;i<len;++i)
            cout<<picked[i]<<endl;
    }

    return 0;
}
