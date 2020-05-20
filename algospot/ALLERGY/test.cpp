#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int n,m;
//canEat: i번 친구가 먹을 수 있는 음식의 집합
//eaters: i번 음식을 먹을수 있는 친구들의 집합
//bit로 표현
long long int canEat[50], eaters[50];
int best;

void init()
{
    cin>>n>>m;
    
    map<string,int> friendsName;
    for(int i=0;i<n;++i)
    {
        string tmp;
        cin>>tmp;
        friendsName[tmp]=i;
    }
    //make eaters
    for(int i=0;i<m;++i)
    {
        int eatersNum;
        cin>>eatersNum;
        
        eaters[i]=0;
        for(int j=0;j<eatersNum;++j)
        {
            string name;
            cin>>name;
            
            long long int bit=(1<<friendsName[name]);
            eaters[i]|=bit;
        }
    }
    //make canEat
    for(int i=0;i<n;++i)
    {
        canEat[i]=0;
        long long int bit=(1<<i);
        for(int j=0;j<m;++j)
            if(bit&eaters[j])
                canEat[i]|=(1<<j);
    }
}

int findBitIndex(long long int num)
{
    int ret=0;
    while(num>1)
    {
        num/=2;
        ++ret;
    }
    return ret;
}

void search(long long int edible, int chosen)
{
    if(chosen>=best)
        return;
    //기저사례 : 전부 먹을 음식이 있는 경우
    if(edible==((1<<n)-1))
    {
        best=chosen;
        return;
    }
    //아직 먹을 음식이 없는 친구를 찾음
    long long int first=(~edible&(edible+1));
    first=findBitIndex(first);
    
    //first친구가 먹을 수 있는 음식을 찾음
    for(int i=0;i<m;++i)
        if(canEat[first]&(1<<i))
            search(edible|eaters[i],chosen+1);
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        init();
        best=n;
        search(0,0);
        cout<<best<<endl;
    }

    return 0;
}
