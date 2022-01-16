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
const int DIR[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

// ------------------------------------------------------

const int MAX_N = 11;

int N;
bool canPlace[MAX_N][MAX_N];
int affected[MAX_N][MAX_N];

void setItem(int y, int x, bool isPlacing) {
	int ny = y;
	int nx = x;
	int minNum = min(ny, nx);
	ny -= minNum;
	nx -= minNum;
	while (nx < N && ny < N) {
		affected[ny][nx] += isPlacing ? 1 : -1;
		nx++;
		ny++;
	}

	ny = y;
	nx = N - x - 1; // x는 좌우 반전해서 구한다.
	minNum = min(ny, nx);
	ny -= minNum;
	nx -= minNum;
	while (nx < N && ny < N) {
		affected[ny][N - nx - 1] += isPlacing ? 1 : -1;
		nx++;
		ny++;
	}
}

int solve(int y, int x) {
	if (x >= N) {
		y++;
		if (N % 2 == 0) {
			if (x == N)
				x = 1;
			else
				x = 0;
		}
		x %= N;
		if (y == N)
			return 0;
	}

	int ret = solve(y, x + 2);
	if (!canPlace[y][x] || affected[y][x]) {
		return ret;
	}
	setItem(y, x, true);
	ret = max(ret, 1 + solve(y, x + 2));
	setItem(y, x, false);
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	memset(affected, 0, sizeof(affected));

	cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> canPlace[i][j];
		}
	}

	cout << solve(0, 0) + solve(0, 1) << endl;

	return 0;
}
