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

int N, M;
vector<string> board;

bool inRange(int y, int x) {
    return 0 <= y && y < M && 0 <= x && x < N;
}

int solve() {
    int minDist[MAX_N][MAX_N];
    queue<pair<pair<int, int>, int>> q;
    q.push({{0, 0}, 0});
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            minDist[i][j] = INF;
        }
    }

    while (!q.empty()) {
        int y = q.front().first.first;
        int x = q.front().first.second;
        int dist = q.front().second;
        q.pop();

        if (dist < minDist[y][x]) {
            minDist[y][x] = dist;
        }
        else {
            continue;
        }

        for (int i = 0; i < 4; ++i) {
            int ny = y + DIR[i][0];
            int nx = x + DIR[i][1];
            if (!inRange(ny, nx)) 
                continue;
            bool isWall = board[ny][nx] == '1';
            int newDist = dist + isWall;
            if (newDist < minDist[ny][nx]) {
                q.push({{ny, nx}, dist + isWall});
            }
        }
    }

    return minDist[M - 1][N - 1];
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> N >> M;

    for (int i = 0; i < M; ++i) {
        string s;
        cin >> s;
        board.push_back(s);
    }

    cout << solve() << endl;

    return 0;
}
