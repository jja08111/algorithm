# 해결 
### 1. 겹치는 부분을 분석하기 
두 볼록 다각형의 교집합은 항상 볼록 다각형이다.  
이를 x축과 수직인 직선으로 잘랐을때 나오는 선분의 길이변화를 보면 유니모달 함수 형태임을 볼 수 있다.  
유니모달 함수는 삼분검색을 이용할 수 있다.  

### 2. 위 껍질과 아래 껍질로 분류하기 
입력값이 시계 반대방향으로 주어지기 때문에 x값이 증가한다면 아래 껍질이고 감소한다면 위 껍질로 분류할 수 있다.  
선분들을 두 좌표값을 저장하여서 표현하였다.  
여기서 마지막 값과 처음값이 만나는데 이를 나머지 연산자로 간단히 구현했다.  
```c++
struct point {
    double x,y;
};

// 입력에 주어진 볼록 다각형 
vector<point> hull1, hull2;
// 위 껍질에 속하는 선분들과 아래 껍길에 속하는 선분들
vector<pair<point,point> > upper, lower;

// 위 껍질과 아래 껍질을 분해
void decompose(const vector<point>& hull)
{
    int n=hull.size();
    for(int i=0;i<n;++i)
    {
        if(hull[i].x<hull[(i+1)%n].x)
            lower.push_back(make_pair(hull[i],hull[(i+1)%n]));
        else if(hull[i].x>hull[(i+1)%n].x)
            upper.push_back(make_pair(hull[i],hull[(i+1)%n]));
    }
}
```
### 3. 삼분검색 구현하기
- 해당 수직선이 어떤 껍질을 지나는지 찾는다.  
- 지난다면 교집합이 되는 껍질을 찾는다.  
- 위 아래 껍질의 거리가 단면의 길이이다.  

위와 같은 과정으로 단면의 길이를 구할 수 있으면 쉽게 삼분검색을 구현할 수 있다.  
여기서 좌우 혹은 상하로 단면이 만나지 않는 경우를 처리하는 방법을 눈여겨 볼 필요가 있다.  
```c++
// [a.x, b.x] 구간 안에 x가 포함되나 확인
bool between(const point& a, const point& b, double x)
{
    return (a.x<=x && x<=b.x) || (b.x<= x && x<=a.x);
}

// (a,b) 선분과 주어진 위치의 수직선이 교차하는 위치의 y값 반환
double at(const point& a, const point& b, double x)
{
    double dy=b.y-a.y, dx=b.x-a.x;
    // 삼각형 비례식 이용
    return a.y+dy*(x-a.x)/dx;
}

// 두 다각형의 교집합을 x위치의 수직선으로 잘랐을 때 단면의 길이를 반환
double vertical(double x)
{
    double minUp=1e20, maxLow=-1e20;
    // 위 껍질의 선분을 순회 하며 최소 y좌표를 찾는다.
    for(int i=0;i<upper.size();++i)
        if(between(upper[i].first, upper[i].second, x))
            minUp=min(minUp,at(upper[i].first, upper[i].second, x));
    // 아래 껍질의 선분을 순회 하며 최소 y좌표를 찾는다.
    for(int i=0;i<lower.size();++i)
        if(between(lower[i].first, lower[i].second, x))
            maxLow=max(maxLow,at(lower[i].first, lower[i].second, x));
    return minUp-maxLow;
}

double solve()
{
    // 수직선이 두 다각형을 모두 만나는 x 좌표의 범위를 구한다.
    double lo=max(minX(hull1),minX(hull2));
    double hi=min(maxX(hull1),maxX(hull2));
    
    // 예외: 두 다각형이 좌우로 배치되어 아예 겹치지 않을 경우
    if(hi<lo)
        return 0;
    
    for(int iter=0;iter<100;++iter)
    {
        double aab=(lo*2+hi)/3.0;
        double abb=(lo+2*hi)/3.0;
        if(vertical(aab)<vertical(abb))
            lo=aab;
        else
            hi=abb;
    }
    // 두 다각형이 겹치지 않게 상하로 배치되면 0.0 을 반환
    return max(0.0,vertical(hi));
}
```
