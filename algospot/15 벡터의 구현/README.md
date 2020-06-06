# 벡터의 구현 
벡터를 이용하면 좌표를 표현하는 많은 것들을 간결하게 구현할 수 있다. 
vector2.cpp 에 벡터를 구조체로 구현한 있는 코드를 볼 수 있다. 

## 점과 직선, 선분의 표현 
세개의 점 p,a,b가 주어졌을 때 a가 b보다 p에 얼마나 더 가까운지 반환하는 함수를 vector2 구조체를 이용하여 간결하게 만들 수 있다. 
```c++
double howMuchCloser(vector2 p, vector2 a, vector2 b) {
    return (b-p).norm()-(a-p).norm();
}
```

## 벡터의 내적
벡터의 내적은 아래와 같이 쓸 수 있다. 
- a · b = ax · bx + ay · by  
      = |a| · |b|cosθ 
```c++
double dot(const vector2& rhs) const {
    return x*rhs.x + y*rhs.y;
}
```

첫 번째 식과 두 번째 식을 이용하면 아래와 같은 내용을 얻을 수 있다. 

### 1. 벡터의 사이각 구하기 
두 번째 정의에서 θ만을 남기고 반대쪽으로 넘기면 다음과 같은 식을 얻을 수 있다. 
- θ = acos{(a · b) / (|a| · |b|)}

### 2. 벡터의 직각 여부 확인하기 
cosθ가 0이라면 θ는 π/2 혹은 3π/2일 수밖에 없다.  
따라서 두 벡터의 내적이 0이라면 두 벡터는 항상 직각이다.  
위에 acos이 있는 식을 사용해서 구할 수도 있으나 이 방법이 그보다 수치적으로 훨씬 안정적이다.  

### 3. 벡터의 사영(vector projection) 
a와 b 벡터가 있을 때 a가 b에 수직으로 드리우는 그림자를 a의 벡터 사영이라고 한다.  
사영한 벡터의 길이는 |a|cosθ인 것을 알 수 있다.  
내적을 통해 |a|cosθ = (a · b) / |b|라는 식을 얻을 수 있는데 이것으로 사영한 결과를 얻을 수 있다.  
이때 b를 단위벡터로 바꾸는 연산을 통해 별도로 나누지 않게 되어 코드를 더욱 간결하게 구현할 수 있다.  
```c++
vector2 project(const vector2& rhs) const {
    vector2 r=rhs.normalize();
    return r*r.dot(*this); 
}
```

## 벡터의 외적 
외적에서 유용한 것은 반환되는 벡터의 방향과 길이이다.  
- a X b = ax · by - ay · bx  
        = |a| · |b|sinθ
```c++
double dot(const vector2& rhs) const {
    return x*rhs.y - rhs.x*y;
}
``` 
외적은 다음과 같은 용도로 사용된다.  

### 1. 면적 계산하기 
|a|sinθ는 a와 b를 두 변으로 하는 평행사변형의 높이이다.  
따라서 외적의 절대값을 이용하여 평행사변형의 넓이를 쉽게 구할 수 있고  
이는 원점과 a,b를 꼭지점으로 하는 삼각형의 넓이를 2로 나누어 구할 수 있다.  

### 2. 두 벡터의 방향 판별 
외적은 어느 방향으로 계산하느냐에 따라 부호가 달라진다.  
- a X b = ax · by - ay · bx = -(ay · bx - ax · by) = -(b X a)  

θ가 양수이면 외적도 양수이고, 음수이면 외적도 음수이다.  
이와 같은 성질을 이용하여 두 벡터의 방향성을 판단할 수 있다.  
a X b가 양수라면 b가 a로부터 반시계방향으로 180도 이내에 있음을 알 수 있다.  
이를 통해 다각형이 볼록한지 오목한지 여부를 판단할 수 있다.  
```c++
//원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계 방향이면 음수,
//평행이면 0을 반환한다.  
double ccw(vector2 a, vector2 b) {
    return a.cross(b);
}
//점 p를 기준으로 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계 방향이면 음수, 
//평행이면 0을 반환한다. 
double ccw2(vector2 p, vector2 a, vector2 b) {
    return ccw(a-p,b-p);
}
```

# 교차와 거리, 면적 
## 직선과 직선의 교차 
직선을 한 점과 방향 벡터로 표현한다.  
- a + p x b  

(https://www.mathfactory.net/11884 에서 직선의 방정식에 관한 내용을 자세히 볼 수 있다.)   
a + p x b 와 c + q x d 의 교점을 구하기 위해서 방정식 a + p x b = c + q x d 을 풀면 된다.  
이 식을 좌표에 대해 나타내면 다음과 같은 연립 방정식을 얻을 수 있다.  
- ax + p x bx = cx + q x dx
- ay + p x by = cy + q x dy

위 식을 p에 대해 풀어 외적으로 간략화 하면 다음과 같다.  
- p = {(c - a) X d} / (b X d)

따라서 결과적으로 구한 p를 a + p x b에 대입해 원하는 점을 구할 수 있다.  
```c++
bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x)
{
    double det=(b-a).cross(d-c);
    //두 선이 평행한 경우 
    if(fabs(det)<EPSILON) return false;
    //b와 d는 각 직선과 평행한 방향 벡터이니 b-a, d-c로 표현하고 있다.  
    x=a+(b-a)*((c-a).cross(d-c)/det);
    return true;
}
```
