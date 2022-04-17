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
//const int DIR[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

// ------------------------------------------------------

const int DIR[3][2] = {{0, 1}, {1, 1}, {1, 0}};
const int MAX_N = 17;

int N;
int board[MAX_N][MAX_N];

bool inRange(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}

int solve(int y, int x, int dir) {
    if (y == N - 1 && x == N - 1) {
        return 1;
    }

    int ret = 0;
    for (int i = 0; i < 3; ++i) {
        if (abs(dir - i) == 2)
            continue;
        int ny = y + DIR[i][0];
        int nx = x + DIR[i][1];

        if (!inRange(ny, nx))
            continue;
        if (board[ny][nx] == 1)
            continue;
        // 대각인 경우
        if (i == 1 && (board[y + 1][x] == 1 || board[y][x + 1] == 1)) {
            continue;
        }
        ret += solve(ny, nx, i);
    }
    return ret;
}

int main(void) {
	ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cin >> board[i][j];
    }

    cout << solve(0, 1, 0) << endl;

    return 0;
}
