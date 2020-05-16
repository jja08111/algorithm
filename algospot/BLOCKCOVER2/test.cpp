#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<vector<pair<int,int> > > rotations;
int blockSize;

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
    sort(rotations.begin(),rotations.end());
    rotations.erase(unique(rotations.begin(),rotations,end()), rotations.end());
    blockSize=rotations[0].size();
}
