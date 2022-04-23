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

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int level[4];
    for (int i = 0; i < 4; ++i) {
        cin >> level[i];
    }
    sort(level, level + 4);

    cout << abs(level[3] + level[0] - level[1] - level[2]) << endl;
    return 0;
}
