const double PI=2.0*acos(0.0);

//2차원 벡터를 표현한다. 
struct vector2 {
    double x, y;
    
    explicit vector2(double x_=0, double y_=0) : x(x_), y(y_) {}
    
    //두 벡터의 비교
    bool operator == (const vector2& rhs) const {
        return x==rhs.x && y==rhs.y;
    }
    bool operator < (const vector2& rhs) const {
        return x!=rhs.x ? x<rhs.x : y<rhs.y;
    }
    
    //벡터의 덧셈과 뺄셈
    vector2 operator + (const vector2& rhs) const {
        return vector2(x+rhs.x, y+rhs.y);
    }
    vector2 operator - (const vector2& rhs) const {
        return vector2(x-rhs.x, y-rhs.y);
    }
    
    //실수로 곱셈
    vector2 operator * (double rhs) const {
        return vector2(x*rhs, y*rhs);
    }
    
    //벡터의 길이를 반환
    double norm() const { return hypot(x,y); }
    
    //방향이 같은 단위 벡터(unit vector)를 반환한다.
    //영벡터에 대해 호출한 경우 반환 값은 정의되지 않는다.
    vector2 normalize() const {
        return vector2(x/norm(), y/norm());
    }
    
    //x축의 양의 방향으로부터 이 벡터까지 반시계 방향으로 잰 각도
    double polar() const {
        return fmod(atan2(y,x)+2*PI, 2*PI);
    }
    
    //벡터의 내적과 외적 구현
    double dot(const vector2& rhs) const {
        return x*rhs.x + y*rhs.y;
    }
    double cross(const vector2& rhs) const {
        return x*rhs.y - rhs.x*y;
    }
    
    //이 벡터를 rhs에 사영한 결과
    vector2 project(const vector2& rhs) const {
        vector2 r=rhs.normalize();
        return r*r.dot(*this); 
    }
};
