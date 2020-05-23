# 해결
### 제약 충족 문제 
이 문제는 스토쿠, n-퀸 문제와 같이 항상 정답이 하나뿐이어서 최적화 문제는 아니고 제약 충족 문제이다.  
이러한 문제는 최적화 기법보다는 아래의 두 가지 정도를 신경써야 한다.
- 답을 일부 생성하고 나면 문제의 조건에 의해 다른 조각의 답에 대해 알게 되는데 이를 **제약 전파** 라고 한다.  
이를 이용하면 실제 탐색해야 할 공간의 수가 크게 줄어들 수 있다.
- 채울 순서를 정함으로서 제약 전파를 더 용이하게 하며, 답을 더 빨리 찾을 확률을 높여준다.  
  * **채울 순서 정하기** 는 **변수 순서 정하기(variable ordering)** 과 **값 순서 정하기(value ordering)** 을 합쳐 부르는 말이다.
  * 이 문제에서는 힌트의 칸이 적은 것부터 찾아가는 순서로 탐색하면 빠르다.  
  
### 후보의 수 계산하기
카쿠로를 손으로 풀다보면 힌트가 가진 칸의 개수가 적은 것 부터 해결하는 것이 효율적이라는 부분을 알게 된다.  
len칸의 합이 sum이고, 이 칸들에 이미 쓰인 수의 집합이 known일 때 나머지 칸에 들어갈 수 있는 숫자의 집합을 반환하는 getCandidated(len,sum, known)를 구현할 수 있다.  
이 함수는 비트마스크를 이용하면 쉽게 구현할 수 있다.
```c++
int getSize(int mask)
{
    return __builtin_popcount(mask);
}

int getSum(int mask)
{
    int ret=0;
    for(int i=1;i<10;++i)
        if(mask&(1<<i))
            ret+=i;
    return ret;
}

int getCandidates(int len, int sum, int known)
{
    int allSets=0;
    for(int set=0;set<1024;set+=2)
        if((set&known)==known && getSize(set)==len && getSum(set)==sum)
            allSets|=set;
    return allSets & ~known;
}
```

### 후보의 수 빠르게 계산하기
하지만 getCandidates()는 탐색 중간마다 계속해서 호출하기에는 너무 많은 연산이 필요하다.  
따라서 입력의 가지수가 대략 20 x 45 x 2^9 => 46만개 정도이기 때문에 미리 후보의 수를 계산해 두는 것이 유리하다.  
여기서 비트마스크를 이용하여 집합의 모든 부분 집합을 간단하게 순회할 수 있다.  
```c++
void generateCandidates()
{
    memset(candidates,0,sizeof(candidates));
    for(int set=0;set<1024;set+=2)
    {
        int l=getSize(set), s=getSum(set);
        //set의 모든 부분집합에 대해 candidates[][][]를 갱신한다.
        int subset=set;
        while(true)
        {
            //전체 숫자의 집합이 set이 되도록 나머지 숫자를 채워넣을 수 있다.
            //known이 subset이니 known을 제외한 set을 추가한다.
            candidates[l][s][subset]|=(set & ~subset);
            if(subset==0)
                break;
            subset=(subset-1)&set;
        }
    }
}
```

### 힌트 칸에 대한 정보 미리 계산하기
좌표가 주어질 때마다 후보의 수를 계산하기 위해 힌트칸을 찾고 길이를 찾고 하기에는 너무 중복되고 시간이 오래걸린다.  
따라서 이 부분도 미리 계산해두면 훨씬 효율적이다.  
```c++
//게임판의 정보
//color: 각 칸의 색깔(0=black or hint cell, 1=white cell)
//value: 각 흰칸에 쓴 숫자(아직 쓰지 않은 칸은 0)
//hint: 각 칸에 해당하는 두 힌트의 번호
int n, color[MAXN][MAXN], value[MAXN][MAXN], hint[MAXN][MAXN][2];

//각 힌트의 정보
//sum: 힌트 칸에 쓰인 숫자
//length: 힌트 칸에 해당하는 흰 칸의 수
//known: 힌트 칸에 해당하는 흰 칸에 쓰인 숫자들의 집합
int hintNum, sum[MAXN*MAXN], length[MAXN*MAXN], known[MAXN*MAXN];

//(y,x)에 val을 쓴다.
void put(int y, int x, int val)
{
    for(int h=0;h<2;++h)
        known[hint[y][x][h]]+=(1<<val);
    value[y][x]=val;
}

//(y,x)에 val을 지운다.
void erase(int y, int x, int val)
{
    for(int h=0;h<2;++h)
        known[hint[y][x][h]]-=(1<<val);
    value[y][x]=0;
}

//힌트 번호가 주어질 때 후보의 집합을 반환한다.
int getCandHint(int hint)
{
    return candidates[length[hint]][sum[hint]][known[hint]];
}

//좌표가 주어질 때 해당 칸에 들어갈 수 있는 후보의 집합을 반환한다.
int getCandCoord(int y, int x)
{
    return getCandHint(hint[y][x][0]) & getCandHint(hint[y][x][1]);
}

void generateHintsData()
{
    cin>>hintNum;
    for(int index=0;index<hintNum;++index)
    {
        int y,x,dir,num;
        cin>>y>>x>>dir>>num;
        --y;--x;
        
        hint[y][x][dir]=index;
        sum[index]=num;
        
        int moveY=0, moveX=0;
        (dir==1) ? moveY=1 : moveX=1;
        
        int nextY=y+moveY, nextX=x+moveX;
        int len=0;
        while(true)
        {
            if(!color[nextY][nextX])
                break;
            hint[nextY][nextX][dir]=index;
            nextY+=moveY;
            nextX+=moveX;
            ++len;
        }
        length[index]=len;
    }
}
```

### 실제 탐색
위와 같은 함수들을 구현해 두면 실제 탐색과정에서 게임판에 대한 정보는 거의 필요없다.  
search()는 매번 후보의 수가 가장 작은 칸을 찾아 이 칸에 숫자를 하나씩 채운다.  
```c++
bool search()
{
    //아직 숫자를 쓰지 않은흰 칸 중 후보의 수가 최소인 칸을 찾는다.
    int y=-1, x=-1, minCands=1023;
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            if(color[i][j]==WHITE && value[i][j]==0)
            {
                int cands=getCandCoord(i,j);
                if(getSize(minCands)>getSize(cands))
                {
                    minCands=cands;
                    y=i; x=j;
                }
            }
    //이 칸에 들어갈 숫자가 없으면 실패
    if(minCands==0)
        return false;
    //모든 칸이 채워졌으면 출력하고 종료한다.
    if(y==-1)
    {
        printSolution();
        return true;
    }
    //현재 칸에 숫자를 채운다.
    for(int val=1;val<=9;++val)
        if(minCands & (1<<val))
        {
            put(y,x,val);
            if(search())
                return true;
            erase(y,x,val);
        }
    return false;
}
```
