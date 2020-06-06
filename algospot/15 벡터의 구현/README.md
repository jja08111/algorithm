# 벡터의 구현 
벡터를 이용하면 좌표를 표현하는 많은 것들을 간결하게 구현할 수 있다. 
vector2.cpp 에 구현되어 있는 코드를 볼 수 있다. 

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

