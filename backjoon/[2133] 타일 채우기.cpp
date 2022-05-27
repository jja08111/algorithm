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

const int MAX = 31;

int N;
int cache[31];

int solve(int here) {
    if (here == N) {
        return 1;
    }

    int &ret = cache[here];
    if (ret != INF) {
        return ret;
    }

    ret = 3 * solve(here + 2);
    for (int width = 4; width + here <= N; width += 2) {
        ret += 2 * solve(here + width);
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(0);

    for (int i = 0; i < MAX; ++i) {
        cache[i] = INF;
    }

    cin >> N;

    cout << solve(0) << endl;

    return 0;
}

