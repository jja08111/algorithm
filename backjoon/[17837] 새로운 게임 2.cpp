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

const int MAX_N = 12 + 1;

class Item;

int N, K;
int board[MAX_N][MAX_N];
vector<Item> items;
vector<int> itemIndexes[MAX_N][MAX_N];

typedef enum {
    White,
    Red,
    Blue
} Color;

typedef enum {
    Right = 1,
    Left,
    Up,
    Down
} Direction;

struct Pos {
    int y;
    int x;
    Pos(int _y, int _x) : y(_y), x(_x) {}
};

class Item {
private:
    int index;
    Pos pos;
    int dir;

public:
    Item(int _index, int _y, int _x, int _dir)
        : index(_index), pos(_y, _x), dir(_dir) {}

    int move() {
        Pos nextPos = createNextPos();
        bool reverse = false;

        if (isOutRangeOrBlue(nextPos)) {
            switchDirection();
            nextPos = createNextPos();
            if (isOutRangeOrBlue(nextPos)) {
                return 0;
            }
        }
        if (isRed(nextPos)) {
            reverse = true;
        }
        moveTogetherAt(nextPos, reverse);
        return itemIndexes[nextPos.y][nextPos.x].size();
    }

private:
    void moveTogetherAt(Pos nextPos, bool shouldReverse) {
        vector<int> &currIndexes = itemIndexes[pos.y][pos.x];
        vector<int> &nextIndexes = itemIndexes[nextPos.y][nextPos.x];
        vector<int> upperItemIndexes;
        vector<int> lowerItemIndexes;
        bool isUpper = false;

        for (int index : currIndexes) {
            if (index == this->index) {
                isUpper = true;
            }

            isUpper
                ? upperItemIndexes.push_back(index)
                : lowerItemIndexes.push_back(index);
        }

        if (shouldReverse) {
            reverse(upperItemIndexes.begin(), upperItemIndexes.end());
        }

        currIndexes = lowerItemIndexes;

        for (int index : upperItemIndexes) {
            nextIndexes.push_back(index);
            items[index].pos = nextPos;
        }
    }
    void switchDirection() {
        switch (dir) {
        case Right:
            dir = Left;
            break;
        case Left:
            dir = Right;
            break;
        case Up:
            dir = Down;
            break;
        case Down:
            dir = Up;
            break;
        }
    }

    Pos createNextPos() {
        return Pos(pos.y + DIR[dir - 1][0], pos.x + DIR[dir - 1][1]);
    }

    bool inRange(Pos pos) {
        return 0 < pos.y && pos.y <= N && 0 < pos.x && pos.x <= N;
    }

    bool isOutRangeOrBlue(Pos pos) {
        return !inRange(pos) || board[pos.y][pos.x] == Blue;
    }

    bool isRed(Pos pos) {
        return board[pos.y][pos.x] == Red;
    }
};

void init() {
    cin >> N >> K;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> board[i][j];
        }
    }
    for (int i = 0; i < K; ++i) {
        int y, x, dir;
        cin >> y >> x >> dir;
        items.push_back(Item(i, y, x, dir));
        itemIndexes[y][x].push_back(i);
    }
}

int runGame() {
    for (int turn = 1; turn <= 1000; ++turn) {
        for (int i = 0; i < items.size(); ++i) {
            if (items[i].move() >= 4) {
                return turn;
            }
        }
    }
    return -1;
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(0);

    init();
    cout << runGame();

    return 0;
}
