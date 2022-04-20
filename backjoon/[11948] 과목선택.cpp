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

    int ret = 0, m = INF;
    for (int i = 0; i < 4; ++i) {
        int n;
        cin >> n;

        ret += n;
        m = min(n, m);
    }
    ret -= m;
    m = INF;
    for (int i = 0; i < 2; ++i)
    {
        int n;
        cin >> n;

        m = min(n, m);
        ret += n;
    }
    ret -= m;

    cout << ret << endl;

    return 0;
}
