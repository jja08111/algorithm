#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

int n;
double dist[101][101];

struct Point {
    double x,y;
    void insert(double a, double b) {
        x=a; y=b;
    }
};

double getDistance(const Point& p1, const Point& p2)
{
    return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}

bool decision(double power)
{
    //첫번째 기지 부터 방문
    long long unVisited=(1<<n)-1-1;
    queue<int> q;
    q.push(0);
    int seen=0;
    while(!q.empty())
    {
        int here=q.front();
        q.pop();
        ++seen;
        for(int there=0;there<n;++there)
            if((unVisited&(1<<there)) && dist[here][there]<=power)
            {
                unVisited^=(1<<there);
                q.push(there);
            }
    }
    return seen==n;
}

double getMinPower()
{
    double lo=0, hi=1416.00;
    for(int iter=0;iter<100;++iter)
    {
        double mid=(lo+hi)/2.0;
        if(decision(mid))
            hi=mid;
        else
            lo=mid;
    }
    return hi;
}

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        cin>>n;
        vector<Point> base(n);
        for(int i=0;i<n;++i)
        {
            double a,b;
            cin>>a>>b;
            base[i].insert(a,b);
        }
        
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                dist[i][j]=getDistance(base[i],base[j]);
        
        printf("%.2lf \n",getMinPower());
    }

    return 0;
}
