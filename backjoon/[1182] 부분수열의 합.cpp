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

int N, S;
vector<int> v;

int solve(int sum, int index, bool ok) {
    if (index == N) {
        if (!ok)
            return 0;
        return sum == S ? 1 : 0;
    }

    return solve(sum + v[index], index + 1, true) + solve(sum, index + 1, ok);
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> N >> S;
    for (int i = 0; i < N; ++i) {
        int n;
        cin >> n;
        v.push_back(n);
    }

    cout << solve(0, 0, false) << endl;

    return 0;
}
