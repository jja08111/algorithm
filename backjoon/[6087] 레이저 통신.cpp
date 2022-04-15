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

int W, H;
vector<string> board;
pair<int, int> targets[2];

class Pos {
public:
    int turnCount;
    int dir;
    int y, x;

    Pos(int _turnCount, int _dir, int _y, int _x)
        : turnCount(_turnCount), dir(_dir), y(_y), x(_x) {}

    bool operator<(const Pos& other) const {
        return turnCount > other.turnCount;
    }
};

bool inRange(int y, int x) {
    return 0 <= y && y < H && 0 <= x && x < W;
}

bool canTurn(int fromDir, int toDir) {
    if (fromDir == 0 && toDir == 1)
        return false;
    if (fromDir == 1 && toDir == 0)
        return false;
    if (fromDir == 2 && toDir == 3)
        return false;
    if (fromDir == 3 && toDir == 2)
        return false;
    return true;
}

int solve(int startY, int startX) {
    priority_queue<Pos> pq;
    int minCount[101][101];

    pq.push(Pos(0, -1, startY, startX));
    for (int i = 0; i < 101; ++i) {
        for (int j = 0; j < 101; ++j) 
            minCount[i][j] = INF;
    }
    minCount[startY][startX] = 0;

    while (!pq.empty()) {
        Pos here = pq.top();
        pq.pop();

        if (here.y == targets[1].first && here.x == targets[1].second) {
            return here.turnCount - 1;
        }

        for (int i = 0; i < 4; ++i) {
            int ny = here.y + DIR[i][0];
            int nx = here.x + DIR[i][1];
            int nextTurnCount = here.turnCount + (here.dir != i);

            if (!inRange(ny, nx) 
                || board[ny][nx] == '*' 
                || minCount[ny][nx] < nextTurnCount
                || !canTurn(here.dir, i))
                continue;

            pq.push(Pos(nextTurnCount, i, ny, nx));
            minCount[ny][nx] = nextTurnCount;
        }
    }
    return INF;
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> W >> H;
    for (int i = 0; i < H; ++i) {
        string s;
        cin >> s;
        board.push_back(s);
    }
    int targetIndex = 0;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (board[i][j] == 'C') {
                targets[targetIndex++] = {i, j};
            }
        }
    }

    cout << solve(targets[0].first, targets[0].second) << endl;

    return 0;
}
