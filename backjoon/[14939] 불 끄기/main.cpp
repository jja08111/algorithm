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

const int RANGE[5][2] = { {1, 0}, {0, 1}, {0, 0}, {-1, 0}, {0, -1} };

string board[101];

bool inRange(int y, int x) {
	return 0 <= y && y < 10 && 0 <= x && x < 10;
}

void switchLight(int y, int x) {
	for (int i = 0; i < 5; ++i) {
		int ny = y + RANGE[i][0];
		int nx = x + RANGE[i][1];
		if (inRange(ny, nx)) {
			board[ny][nx] = board[ny][nx] == 'O' ? '#' : 'O';
		}
	}
}

int solve(int y, int x) {
	if (x > 0 && y > 0 && board[y - 1][x - 1] == 'O') {
		return INF;
	}
	if (x > 1 && y == 9 && board[9][x - 2] == 'O') {
		return INF;
	}
	if (x == 10) {
		x = 0;
		++y;
		if (y == 10) {
			return board[9][9] == 'O' ? INF : 0;
		}
	}

	int ret = solve(y, x + 1);

	switchLight(y, x);
	ret = min(ret, solve(y, x + 1) + 1);
	switchLight(y, x);

	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(0); cin.tie(0);

	for (int i = 0; i < 10; ++i) {
		cin >> board[i];
	}

	int ret = solve(0, 0);
	if (ret == INF)
		cout << -1 << endl;
	else 
		cout << ret << endl;
	return 0;
}


