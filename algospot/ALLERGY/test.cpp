#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n,m;
//canEat: i번 친구가 먹을 수 있는 음식의 집합
//eaters: i번 음식을 먹을수 있는 친구들의 집합
//bit로 표현
int canEat[50], eaters[50];

void init()
{
    cin>>n>>m;
    
    vector<string> friendsName;
    for(int i=0;i<n;++i)
    {
        string tmp;
        cin>>tmp;
        friendsName.push_back(tmp);
    }
    //make eaters
    for(int i=0;i<m;++i)
    {
        int eatersNum,sumBit=0;
        cin>>eatersNum;
        for(int j=0;j<eatersNum;++j)
        {
            string name;
            cin>>name;
            
            int pos=find(friendsName.begin(),friendsName.end(),name)-friendsName.begin();
            int bit=(1<<pos);
            sumBit|=bit;
        }
        eaters[i]=sumBit;
    }
    //make canEat
    for(int i=0;i<n;++i)
    {
        int sumBit=0;
        int bitmask=(1<<i);
        for(int j=0;j<m;++j)
            if(bitmask&eaters[j])
                sumBit|=(1<<j);
        
        canEat[i]=sumBit;
        printf("%d ### ",canEat[i]);
    }
    
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        init();
    }

    return 0;
}
