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
    Pos pos;
    int dir;
    bool isBottom = true;

public:
    Item(int _y, int _x, int _dir)
        : pos(_y, _x), dir(_dir) {}

    void move() {
        if (!isBottom)
            return;

        Pos nextPos = createNextPos();

        if (isOutRangeOrBlue(nextPos)) {
            switchDirection();
            nextPos = createNextPos();
            if (isOutRangeOrBlue(nextPos)) {
                return;
            }
        }
        if (isRed(nextPos)) {
            reverseTogether();
        }
        moveTogetherAt(nextPos);
    }
private:
    void moveTogetherAt(Pos targetPos) {
        Pos prevPos = Pos(pos);
        vector<int> indexes = itemIndexes[pos.y][pos.x];
        vector<int>& targetIndexes = itemIndexes[targetPos.y][targetPos.x];

        for (int index : indexes) {
            items[index].pos = targetPos;
            items[index].isBottom = targetIndexes.empty();
            targetIndexes.push_back(index);
        }
        itemIndexes[prevPos.y][prevPos.x].clear();
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
    void reverseTogether() {
        vector<int>& indexes = itemIndexes[pos.y][pos.x];
        vector<int> reversed;
        for (int i = indexes.size() - 1; i >= 0; i--) {
            int index = indexes[i];
            items[index].isBottom = reversed.empty();
            reversed.push_back(index);
        }
        itemIndexes[pos.y][pos.x] = reversed;
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
        items.push_back(Item(y, x, dir));
        itemIndexes[y][x].push_back(i);
    }
}

bool isGameOver() {
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (itemIndexes[i][j].size() >= 4)
                return true;
        }
    }
    return false;
}

int runGame() {
    int turn = 0;
    while (!isGameOver()) {
        for (int i = 0; i < items.size(); ++i) {
            items[i].move();
        }
        turn++;
        if (turn >= 1000)
            return -1;
    }
    return turn;
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(0);

    init();
    cout << runGame();

    return 0;
}
