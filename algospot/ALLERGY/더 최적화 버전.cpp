#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

int n,m;
//canEat: i번 친구가 먹을 수 있는 음식의 집합
//eaters: i번 음식을 먹을수 있는 친구들의 집합
//bit로 표현
long long int canEat[50], eaters[50];
int best;
map<int,int> convertIndex;

void preCacl()
{
    int num=1;
    for(int i=0;i<50;++i)
    {
        convertIndex[num]=i;
        num*=2;
    }
}

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
    for(int i=0;i<50;++i)
        canEat[i]=eaters[i]=0;
    for(int i=0;i<m;++i)
    {
        int eatersNum;
        cin>>eatersNum;
        
        for(int j=0;j<eatersNum;++j)
        {
            string name;
            cin>>name;
            
            eaters[i]|=(1LL<<index[name]);
            canEat[index[name]]|=(1LL<<i);
        }
    }
    preCacl();
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
    long long int first=(~edible&(edible+1));
    first=convertIndex[first];
    
    //first친구가 먹을 수 있는 음식을 찾음
    for(int food=0;food<m;++food)
        if(canEat[first]&(1LL<<food))
            search(edible|eaters[food],chosen+1);
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
