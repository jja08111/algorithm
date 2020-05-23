#include <iostream>
#include <cstring>
using namespace std;

const int MAXN=20;
const int WHITE=1;
//candidates[len][sum][known]
int candidates[10][46][1024];

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

/*
int getCandidates(int len, int sum, int known)
{
    int allSets=0;
    for(int set=0;set<1024;set+=2)
        if((set&known)==known && getSize(set)==len && getSum(set)==sum)
            allSets|=set;
    return allSets & ~known;
}
*/

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

void generateHintsData(int index)
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

void init()
{
    cin>>n;
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
        {
            cin>>color[i][j];
            value[i][j]=0;
            hint[i][j][0]=hint[i][j][1]=0;
        }
    memset(sum,0,sizeof(sum));
    memset(length,0,sizeof(length));
    memset(known,0,sizeof(known));
    
    cin>>hintNum;
    for(int idx=0;idx<hintNum;++idx)
        generateHintsData(idx);
    generateCandidates();
}

void printSolution()
{
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
            cout<<value[i][j]<<" ";
        cout<<endl;
    }
}

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

int main()
{
    int testCase;
    cin>>testCase;
    while(testCase--)
    {
        init();
        search();
    }

    return 0;
}
