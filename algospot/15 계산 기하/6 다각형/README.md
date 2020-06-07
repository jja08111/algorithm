# 다각형 
## 면적 구하기
```c++
//주어진 단순 다각형 p의 넓이를 구한다.
//p는 각 꼭지점의 위치 벡터의 집합으로 주어진다. 
double area(const vector<vector2>& p)
{
    double ret=0;
    for(int i=0;i<p.size();++i)
    {
        int j=(i+1)%p.size();
        ret+=p[i].x*p[j].y-p[j].x*p[i].y;
    }
    return fabs(ret)/2.0;
}
```
