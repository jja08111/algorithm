# 해결 
벡터를 이용하여 해결하면 비교적 쉽게 구현할 수 있다.  
먼저 문제를 간단하게 하기 위해서 공을 점으로 바꾸고 장애물의 반지름을 1씩 증가시킨다.  
그 후 전체적인 시뮬레이션의 큰 흐름은 다음과 같다.  
1. 공의 현재 위치와 방향을 파악한다.  
2. 가장 먼저 충돌하는 장애물을 찾는다.  
3. 충돌후의 공의 위치와 방향을 파악한다.  
4. 더이상 충돌할 장애물이 없거나 100번째 충돌을 찾을 때까지 반복한다.  

### 공과 장애물의 충돌 지점 찾기 
공의 궤적을 시간 t에 대해 공의 위치 벡터 p와 방향 벡터 q를 이용해 다음과 같이 표현할 수 있다.  
- f(t) = q + t × d (t ≥ 0)

그렇다면 중심이 c이고 반지름이 r인 원과 공이 교차하는 시간은 다음과 같다.  
- |c - f(t)| = r

|a|² = a·a 인 벡터의 성질을 이용한다.  
- (c - f(t))×(c - f(t)) = r²

위의 식을 t에 대해 정리하면 이차방정식을 얻을 수 있다.  
- d · d · t² + 2(p - c) - d · t + c · c + p · p - 2(c · p) - r² = 0

방정식의 계수는 벡터가 아닌 실수가 되었으니 이차방정식을 풀면 언제 공의 궤적과 장애물이 교차하는지 알 수 있다.  
여기서 먼저 장애물에 충돌하는 값을 찾아야 하니 이 방정식의 양수해를 모두 구하고, 그중 최소치를 찾으면 된다.  
구현 할 때에는 아래와 같은 예외처리를 주의해야 한다.  
1. 2차 방정식의 실근이 없는 경우 공의 궤적과 장애물은 충돌하지 않는다.  
2. 반환된 실근 중 0 이하의 값은 무시해야 한다.  
  (음수는 진행 방향 뒷쪽에서 교차하는 것이다.)  
  (0은 이미 공과 장애물이 접해있는 상태이다.)
```c++
//2차 방정식 ax^2 + bx + c = 0 의 모든 실근을 크기 순서대로 반환한다.
vector<double> solve2(double a, double b, double c)
{
    double d=b*b - 4*a*c;
    //해가 없는 경우 
    if(d < -EPSILON)
        return vector<double>();
    //중근
    if(d < EPSILON)
        return vector<double>(1, -b/(2*a));
    
    vector<double> ret;
    ret.push_back((-b-sqrt(d))/(2*a));
    ret.push_back((-b+sqrt(d))/(2*a));
    return ret;
}

//here에 있던 공이 1초마다 dir만큼 굴러갈 때, center를 중심으로 하고
//반지름 radius인 장애물과 몇 초 후에 충돌하는지 반환한다.
//충돌하지 않을 경우 INFTY를 반환한다.
double hitCircle(vector2 here, vector2 dir, vector2 center, int radius)
{
    double a=dir.dot(dir);
    double b=2*dir.dot(here-center);
    double c=center.dot(center)+here.dot(here)-2*here.dot(center)-radius*radius;
    
    vector<double> sols=solve2(a,b,c);
    //충돌하지 않을 때
    if(sols.empty() || sols[0]<EPSILON)
        return INFTY;
    return sols[0];
}
```

### 반사 처리 
벡터의 사영을 이용하여 간단하게 구현할 수 있다.  
```c++
//here에 있던 공이 dir 방향으로 굴러와 center를 중심으로 하는 장애물에서
//contact 위치에서 충돌했을 때 공의 새로운 방향을 반환한다.
vector2 reflect(vector2 dir, vector2 center, vector2 contact)
{
    return (dir-dir.project(contact-center)*2).normalize();
}
```

### 시뮬레이션 구현 
```c++
//공의 현재 위치와 방향이 주어질 때 최대 100번의 충돌을 출력한다.
void simulate(vector2 here, vector2 dir)
{
    dir=dir.normalize();
    int hitCount=0;
    while(hitCount<100)
    {
        //이번에 충돌할 장애물을 찾는다.
        int circle=-1;
        double time=INFTY*0.5;
        //각 장애물을 순회하며 가장 먼저 만나는 장애물을 찾는다.
        for(int i=0;i<n;++i)
        {
            double cand=hitCircle(here,dir,center[i],radius[i]+1);
            if(cand<time)
            {
                time=cand;
                circle=i;
            }
        }
        //더이상 장애물에 충돌하지 않고 게임판을 벗어난 경우
        if(circle==-1) break;
        
        //부딪히는 장애물의 번호를 출력한다.
        if(hitCount++) 
            cout<<" ";
        cout<<circle;
        //공의 새 위치를 계산한다.
        vector2 contact=here+dir*time;
        //부딪힌 위치와 새 방향으로 here과 dir을 변경한다.
        dir=reflect(dir,center[circle],contact);
        here=contact;
    }
    cout<<endl;
}
```

# 참고
1. "알고리즘 문제 해결 전략", 구종만
2. [원의 방정식 벡터로 표현](https://m.blog.naver.com/PostView.nhn?blogId=777bobos&logNo=220140045711&proxyReferer=https:%2F%2Fwww.google.com%2F)
