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

const int MAX_N = 101;

int N, M, R;
int itemCount[MAX_N];
int dist[MAX_N][MAX_N];

void floyd() {
    for (int t = 1; t <= N; ++t) {
        for (int u = 1; u <= N; ++u) {
            for (int v = 1; v <= N; ++v) {       
                dist[u][v] = min(dist[u][v], dist[u][t] + dist[t][v]);
            }
        }
    }
}

int countItems(int start) {
    int ret = 0;
    for (int i = 1; i <= N; ++i) {
        if (dist[start][i] <= M) {
            ret += itemCount[i];
        }
    }
    return ret;
}

int main(void) {
	ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> N >> M >> R;
    for (int i = 1; i <= N; ++i) {
        cin >> itemCount[i];
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            dist[i][j] = i == j ? 0 : INF;
        }
    }

    for (int i = 0; i < R; ++i) {
        int a, b, l;
        cin >> a >> b >> l;
        dist[a][b] = l;
        dist[b][a] = l;
    }

    floyd();

    int ret = 0;
    for (int i = 1; i <= N; ++i) {
        ret = max(ret, countItems(i));
    }
    cout << ret << endl;

    return 0;
}
