# 해결 
입력 값을 x,y라고 하고 좌표위에 나타내면 해결 방법이 떠오른다.  
새로운 사람이 등록 될 때마다 이 사람이 다른 사람에게 지배 당하는지, 혹은 다른 사람을 지배하는지 확인하는 것이다.  
즉, 입력된 값들이 좌표상에서 계단식의 모양을 띄어야만 한다.  
이때는 새로운 값을 기준으로 바로 오른쪽 값을 확인하면 된다.  

입력의 추가와 삭제를 빠르게 해야 하기 때문에 이진 검색 트리를 이용하면 된다.  
그리고 정렬된 자료에서 바로 오른쪽 값을 확인하기 용이한 lower_bound를 이용할 수 있는 map<int,int>를 사용하는 것이 좋다.  

### 새로운 값이 지배되는가?
아래의 함수는 새로운 값이 다른 값에 지배 되는지 확인하기 위한 함수이다.  
바로 오른쪽 값을 비교하여 판단하고 있다. 예외로 새로운 값이 제일 오른쪽에 있는 경우를 처리하고 있다.  
```c++
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
```

### 새로운 값이 지배하는 값을 지우자
다음 함수는 새로운 값이 지배하는 값들을 지우는 함수이다. 새로운 값보다 왼쪽 값이 더 커서 더 이상 지울수 없을 때까지 지운다.  
예외로 새로운 값이 가장 왼쪽 값인 경우, 왼쪽 점이 더 작은데 제일 처음일 경우 지우고 바로 종료하는 경우를 볼 수 있다.  
```c++
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
```

### 문제 해결 
위 함수들을 이용하여 새로운 값이 다른 값들에 지배되는 경우 값을 트리에 추가하지 않고 바로 트리의 크기를 반환하며,  
그렇지 않으면 새로운 값에 지배되는 값들을 지우고 새로운 값을 추가하여 크기를 반환한다.  
```c++
int registered(int x, int y)
{
    if(isDominated(x,y))
        return coords.size();
    removeDominated(x,y);
    coords[x]=y;
    return coords.size();
}
```
