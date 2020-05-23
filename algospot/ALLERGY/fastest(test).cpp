#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <functional>
using namespace std;

int n,m;
//canEat: i번 친구가 먹을 수 있는 음식의 집합
//eaters: i번 음식을 먹을수 있는 친구들의 집합
//bit로 표현
long long int canEat[50];
//먹을수 있는 사람이 많은 순으로 해야한다.
//first=>먹을 수 있는 사람의 수
//second.first=>먹을 수 있는 사람의 bit, second.second=>음식의 index
vector<pair<int,pair<long long int,int> > > eaters;
int best;

void init()
{
    cin>>n>>m;
    best=m;
    
    map<string,long long> index;
    for(int i=0;i<n;++i)
    {
        string name;
        cin>>name;
        index[name]=i;
    }
    //make canEat, eaters
    eaters.clear();
    for(int i=0;i<50;++i)
        canEat[i]=0;
    for(int i=0;i<m;++i)
    {
        int eatersNum;
        cin>>eatersNum;
        
        long long int bitmask=0;
        for(int j=0;j<eatersNum;++j)
        {
            string name;
            cin>>name;
            
            bitmask|=(1LL<<index[name]);
            canEat[index[name]]|=(1LL<<i);
        }
        eaters.push_back(make_pair(__builtin_popcount(bitmask),make_pair(bitmask,i)));
    }
    sort(eaters.begin(),eaters.end(),greater<pair<int,pair<long long int,int> > >());
}

int minimum(long long int edible)
{
    int minFriend,minCount=50;
    for(int i=0;i<n;++i)
        if(~edible&(1LL<<i))
        {
            int count=__builtin_popcount(canEat[i]);
            if(count<minCount)
            {
                minCount=count;
                minFriend=i;
            }
        }
    return minFriend;
}

void search(long long int edible, int chosen)
{
    if(chosen>=best)
        return;
    //기저사례 : 전부 먹을 음식이 있는 경우
    if(edible==((1LL<<n)-1))
    {
        best=chosen;
        return;
    }
    //아직 먹을 음식이 없는 친구를 찾음
    int first=minimum(edible);
    
    //first친구가 먹을 수 있는 음식을 찾음
    vector<pair<int,pair<long long int,int> > >::iterator food;
    for(food=eaters.begin();food!=eaters.end();++food)
        if(canEat[first]&(1LL<<(food->second.second)))
            search(edible|(food->second.first),chosen+1);
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        init();
        search(0,0);
        cout<<best<<endl;
    }

    return 0;
}
