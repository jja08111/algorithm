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

void init()
{
    cin>>n>>m;
    
    map<string,int> index;
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
            
            eaters[i]|=(1<<index[name]);
            canEat[index[name]]|=(1<<i);
        }
    }
}

void convertIndex(long long int& input)
{
    int ret=0, num=input;
    while(num>1)
    {
        num/=2;
        ++ret;
    }
    input=ret;
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
    convertIndex(first);
    
    //first친구가 먹을 수 있는 음식을 찾음
    for(int food=0;food<m;++food)
        if(canEat[first]&(1<<food))
            search(edible|eaters[food],chosen+1);
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        init();
        best=m;
        search(0,0);
        cout<<best<<endl;
    }

    return 0;
}
