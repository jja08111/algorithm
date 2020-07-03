#include <iostream>
#include <map>
using namespace std;

// coords[x]=y
map<int,int> coords;

bool isDominated(int x, int y)
{
    map<int,int>::iterator it=coords.lower_bound(x);
    // 새로운 값이 제일 오른쪽에 있어 지배 당하지 않을 경우
    if(it==coords.end())
        return false;
    // 새로운 값의 y값이 바로 오른쪽에 있는 값에 지배 당하는가?
    return y < it->second;
}

void removeDominated(int x, int y)
{
    map<int,int>::iterator it=coords.lower_bound(x);
    // 새로운 값이 가장 왼쪽에 있을 경우
    if(it==coords.begin())
        return;
    // 새로운 값의 왼쪽 값을 가르킨다.
    --it;
    while(true)
    {
        // 왼쪽 값이 새로운 값보다 커서 지배하지 않으면 종료 
        if(it->second > y) 
            break;
        // 왼쪽 점이 더 없으므로 it만 지우고 종료
        if(it==coords.begin())
        {
            coords.erase(it);
            break;
        }
        // 이전 점으로 이터레이터를 하나 옮겨 놓고 it을 지움
        else
        {
            map<int,int>::iterator jt=it;
            --jt;
            coords.erase(it);
            it=jt;
        }
    }
}

int registered(int x, int y)
{
    if(isDominated(x,y))
        return coords.size();
    removeDominated(x,y);
    coords[x]=y;
    return coords.size();
}

int main()
{
    int testcase;
    cin>>testcase;
    while(testcase--)
    {
        coords.clear();
        
        int n,x,y,ret=0;
        scanf("%d",&n);
        for(int i=0;i<n;++i)
        {
            scanf("%d %d",&x,&y);
            ret+=registered(x,y);
        }
        
        cout<<ret<<endl;
    }
    
    return 0;
}
