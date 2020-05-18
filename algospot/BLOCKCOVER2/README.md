# 해결
이 문제는 이전에 보았던 boardcover문제와 유사한 문제이다.  
하지만 난이도는 훨씬 어렵다.  
차이점은 아래와 같다.  
- 블록의 모양이 입력에 따로 주어진다.  
- 빈 공간이 존재 할 수 있다.  
- 최대로 배치가능한 개수를 구하는 문제다.

## 1. 블록형성
- 블록을 쉽게 형성하기 위해 원점을 정하고 블록을 한칸씩 상대좌표로 저장한다.  
그리고 블록을 90도 시계방향으로 회전하여 다시 상대좌표로 저장하는 작업을 반복한다.  
- 그 후 중복되는 블록이 있을 수 있으니 정렬후 unique 함수를 이용하여 중복되는 부분을 뒤로 옮기고, 그 부분을 지워 중복을 제거할 수 있다.  
```c++
int blockSize;
vector<vector<pair<int,int> > > rotations;

vector<string> rotate(const vector<string>& arr)
{
    //90도 회전해야 하니 arr[0].size()와 arr.size()의 위치가 바뀐것을 눈여겨 보자
    vector<string> ret(arr[0].size(),string(arr.size(),' '));
    for(int i=0;i<arr.size();++i)
        for(int j=0;j<arr[0].size();++j)
            ret[j][arr.size()-1-i]=arr[i][j];
    return ret;
}

void generateRotations(vector<string> block)
{
    rotations.clear();
    rotations.resize(4);
    for(int rot=0;rot<4;++rot)
    {
        int originY=-1, originX=-1;
        for(int i=0;i<block.size();++i)
            for(int j=0;j<block[i].size();++j)
                if(block[i][j]=='#')
                {
                    //가장 윗줄 맨 왼쪽에 있는 칸이 원점이 된다.
                    if(originY==-1)
                    {
                        originY=i;
                        originX=j;
                    }
                    //각 칸의 위치를 원점으로부터의 상대좌표로 표현한다.
                    rotations[rot].push_back(make_pair(i-originY,j-originX));
                }
        //블록을 시계방향으로 90도 회전한다.
        block=rotate(block);
    }
    //중복되는 블럭을 제거한다.
    sort(rotations.begin(),rotations.end());
    rotations.erase(unique(rotations.begin(),rotations.end()), rotations.end());
    blockSize=rotations[0].size();
}
```

## 2. 빈공간 해결 
빈공간은 '막아'둬서 블록을 추가 배치하지 않고 재귀호출하여 해결 할 수 있다. 
```c++
//이 칸을 덮지 않고 '막아'둔다.
isCovered[y][x]=1;
search(placedBlockNum);
isCovered[y][x]=0;
```

## 3. 가지치기
현재까지의 방법으로는 시간초과하여 해결할 수 없다.  
따라서 가지치기가 필요하다.  
방법은 남은 빈칸의 수가 블록을 한칸씩 쪼개어 넣을때 몇개 배치할 수 있는지와 현재의 최적해와 비교하면 된다.  
즉, 현재의 최적해가 아무리 블록을 욱여넣어도 더 클때 탐색을 중단하는 것이다.
```c++
bool canPruneBlock(int placedBlockNum)
{
    int emptyCell=0;
    for(int i=0;i<boardHeight;++i)
        for(int j=0;j<boardWidth;++j)
            emptyCell+=(isCovered[i][j]==0 ? 1 : 0);
    //남은 칸 개수가 블록을 놓아도 현재의 최적해보다 작거나 같을때
    return (emptyCell/blockSize)+placedBlockNum<=best;
}
```
# 회고
아주 간단한 오타 때문에 디버깅하는데 시간을 엄청 썼다.
```c++
//cin>>boardHeight>>boardWidth>>blockHeight>>boardWidth;
cin>>boardHeight>>boardWidth>>blockHeight>>blockWidth;
```
