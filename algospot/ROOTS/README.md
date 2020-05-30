# 해결 
2차 방정식 까지는 근의 공식을 이용하여 문제를 해결할 수 있지만 그 이상의 방정식은 공식이 복잡하거나 공식 자체가 없는 경우가 있다.  
이러한 문제의 해결 방법은 아래와 같다.  
1. 극점과 극점 사이에서 근을 찾을 수 있다.  
    ->재귀호출로 다항식을 미분하여 기울기가 0이 되는 지점을 찾는다.  
2. 이분법을 이용하여 근을 찾는다.  
3. 맨 오른쪽 혹은 맨 왼쪽의 근의 경우는 근의 범위 바깥의 값을 추가하여 해결한다.  
```c++
vector<double> solve(const vector<double>& poly)
{
    int n=poly.size()-1;
    
    // 기저사례: 2차 이하의 방정식들은 풀 수 있다.
    if(n<=2)
        return solveNavie(poly);
    
    // 방정식을 미분해서 n-1차 방정식을 얻는다.
    vector<double> derivative=differentiate(poly);
    vector<double> sols=solve(derivative);
    
    // 이 극점들 사이를 하나하나 검사하며 근이 있나 확인한다.
    sols.insert(sols.begin(), -LIMIT-1);
    sols.insert(sols.end(), LIMIT+1);
    vector<double> ret;
    for(int i=0;i+1<sols.size();++i)
    {
        double x1=sols[i], x2=sols[i+1];
        double y1=evaluate(poly,x1), y2=evaluate(poly,x2);
        // f(x1)과 f(x2)의 부호가 같은 경우 답은 없다.
        if(y1*y2>0)
            continue;
        // 불변 조건: f(x1)<=0<(fx2)
        if(y1>y2)
        {
            swap(y1,y2);
            swap(x1,x2);
        }
        // 이분법 이용
        for(int iter=0;iter<100;++iter)
        {
            double mx=(x1+x2)/2;
            double my=evaluate(poly,mx);
            if(y1*my>0)
            {
                y1=my;
                x1=mx;
            }
            else
            {
                y2=my;
                x2=mx;
            }
        }
        ret.push_back((x1+x2)/2);
    }
    sort(ret.begin(),ret.end());
    return ret;
}
```
