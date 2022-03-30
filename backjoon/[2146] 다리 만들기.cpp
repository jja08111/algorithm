#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <cstring>
#include <stack>
#include <cmath>
#include <climits>
#include <cctype>
using namespace std;

const int INF = 987654321;  
const int MOD = 1000000000 + 7;
const int DIR[4][2] = { {0, 1}, {0, -1}, {-1, 0}, {1, 0} };

// ------------------------------------------------------

const int MAX_N = 101;

int N;
int board[MAX_N][MAX_N];

bool inRange(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}

void markBoard(int y, int x, int flag) {
    board[y][x] = flag;
    for (int i = 0; i < 4; ++i) {
        int ny = y + DIR[i][0];
        int nx = x + DIR[i][1];
        if (!inRange(ny, nx) || board[ny][nx] != 1)
            continue;
        markBoard(ny, nx, flag);
    }
}

int getNearbyFlagNum(int y, int x) {
    for (int i = 0; i < 4; ++i) {
        int ny = y + DIR[i][0];
        int nx = x + DIR[i][1];
        if (!inRange(ny, nx))
            continue;
        
        int flagNum = board[ny][nx];
        if (flagNum > 1) {
            return flagNum;
        }
    }
    return -1;
}

int countMinBridge(int y, int x, int sourceFlag) {
    queue<pair<pair<int, int>, int>> q;
    bool discovered[MAX_N][MAX_N];
    memset(discovered, false, sizeof(discovered));
    q.push({{y, x}, 0});
    discovered[y][x] = true;

    while (!q.empty()) {
        int cy = q.front().first.first;
        int cx = q.front().first.second;
        int count = q.front().second;
        q.pop();

        if (board[cy][cx] != sourceFlag && board[cy][cx] != 0) {
            return count;
        }

        for (int i = 0; i < 4; ++i) {
            int ny = cy + DIR[i][0];
            int nx = cx + DIR[i][1];
            if (!inRange(ny, nx) || discovered[ny][nx] || board[ny][nx] == sourceFlag) 
                continue;
            
            discovered[ny][nx] = true;
            q.push({{ny, nx}, count + 1});
        }
    }
    return INF;
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; ++i) 
        for (int j = 0; j < N; ++j)
            cin >> board[i][j];

    int flag = 2;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == 1) {
                markBoard(i, j, flag);
                flag++;
            }
        }

    int ret = INF;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == 0) {
                int nearbyFlagNum = getNearbyFlagNum(i, j);
                if (nearbyFlagNum == -1)
                    continue;
                ret = min(ret, countMinBridge(i, j, nearbyFlagNum));
            }
        }
    }
    cout << ret << endl;

    return 0;
}
