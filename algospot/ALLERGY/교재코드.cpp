#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int friendNum,foodNum;
//canEat: i번 친구가 먹을 수 있는 음식의 집합
//eaters: i번 음식을 먹을수 있는 친구들의 집합
vector<int> canEat[50], eaters[50];
int best;

void init()
{
    cin>>friendNum>>foodNum;
    best=foodNum;
    
    map<string,int> index;
    for(int i=0;i<friendNum;++i)
    {
        string name;
        cin>>name;
        index[name]=i;
    }
    //make eaters
    for(int food=0;food<foodNum;++food)
    {
        int eatersNum;
        cin>>eatersNum;
        for(int i=0;i<eatersNum;++i)
        {
            string name;
            cin>>name;
            
            eaters[food].push_back(index[name]);
            canEat[index[name]].push_back(food);
        }
    }
}

void search(vector<int>& edible, int chosen)
{
    if(chosen>=best)
        return;
    //아직 먹을 음식이 없는 친구를 찾음
    int first=0;
    while(first<friendNum && edible[first]>0)
        ++first;
    //기저사례 : 전부 먹을 음식이 있는 경우
    if(first==friendNum)
    {
        best=chosen;
        return;
    }
    //first친구가 먹을 수 있는 음식을 찾음
    for(int i=0;i<canEat[first].size();++i)
    {
        int food=canEat[first][i];
        for(int j=0;j<eaters[food].size();++j)
            edible[eaters[food][j]]++;
        search(edible,chosen+1);
        for(int j=0;j<eaters[food].size();++j)
            edible[eaters[food][j]]--;
    }
}

void clear()
{
    for(int i=0;i<friendNum;++i)
        canEat[i].clear();
    for(int i=0;i<foodNum;++i)
        eaters[i].clear();
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        init();
        
        vector<int> edible(friendNum,0);
        search(edible,0);
        
        cout<<best<<endl;
        clear();
    }

    return 0;
}
