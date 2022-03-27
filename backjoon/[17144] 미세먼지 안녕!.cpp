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
const int DIR[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

// ------------------------------------------------------

const int MAX = 1001;

int R, C, T;
int board[MAX][MAX];
int diffusions[MAX][MAX];
int filterPosition[2][2];

bool inRange(int y, int x) {
    return 0 <= y && y < R && 0 <= x && x < C;
}

void diffusion() {
    memset(diffusions, 0, sizeof(diffusions));

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (board[i][j] == -1)
                continue;
            int count = 0;
            int diffusionSize = board[i][j] / 5;
            if (diffusionSize == 0)
                continue;
            for (int d = 0; d < 4; ++d) {
                int ny = i + DIR[d][0];
                int nx = j + DIR[d][1];
                if (!inRange(ny, nx) || board[ny][nx] == -1) {
                    continue;
                }

                diffusions[ny][nx] += diffusionSize;
                count++;
            }
            board[i][j] -= count * diffusionSize;
        }
    }
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (board[i][j] != -1) {
                board[i][j] += diffusions[i][j];
            }
        }
    }
}

void flowAir(bool isTop) {
    const int index = isTop ? 0 : 1;
    const int yDir = isTop ? -1 : 1;
    const int startY = filterPosition[index][0];

    int ny = startY + 2 * yDir;
    int nx = filterPosition[index][1];
    int y = startY + yDir;
    int x = filterPosition[index][1];
    int temp = 0;

    while (true) {
        board[y][x] = board[ny][nx];

        y = ny;
        int candNextY = ny + yDir;
        if (0 <= candNextY && candNextY < R) {
            ny = candNextY;
        } else {
            nx++;
            break;
        }
    }

    while (true) {
        board[y][x] = board[ny][nx];

        x = nx;
        if (nx + 1 < C) {
            nx++;
        } else {
            ny -= yDir;
            break;
        }
    }

    while (true) {
        board[y][x] = board[ny][nx];

        y = ny;
        int candNextY = ny - yDir;
        if ((isTop && (0 <= candNextY && candNextY <= startY)) 
        || (!isTop && (startY <= candNextY && candNextY < R))) {
            ny = candNextY;
        } else {
            nx--;
            break;
        }
    }

    while (true) {
        board[y][x] = board[ny][nx] == -1 ? 0 : board[ny][nx];

        x = nx;
        if (nx - 1 >= 0) {
            nx--;
        } else {
            break;
        }
    }
}

int countMicroDust() {
    int result = 0;
     for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (board[i][j] != -1) {
                result += board[i][j];
            }
        }
    }
    return result;
}

void printState() {
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "=============" << endl;
}

int main(void) {
	ios_base::sync_with_stdio(0); cin.tie(0);

    int filterCount = 0;

    cin >> R >> C >> T;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cin >> board[i][j];
            if (board[i][j] == -1) {
                filterPosition[filterCount][0] = i;
                filterPosition[filterCount++][1] = 0;
            }
        }
    }

    while (T--) {
        diffusion();
        flowAir(true);
        flowAir(false);
    }
    cout << countMicroDust() << endl;

    return 0;
}
