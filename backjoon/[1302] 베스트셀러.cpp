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

    int n;
    map<string, int> m;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;

        auto it = m.find(s);
        if (it == m.end()) {
            m.insert({s, 1});
        }
        else {
            m[s] = it->second + 1;
        }
    }

    string result = "";
    int maxCount = 0;
    for (auto it = m.begin(); it != m.end(); ++it) {
        if (it->second >= maxCount) {
            if (it->second > maxCount || it->first < result) {
                result = it->first;
                maxCount = it->second;
            }
        }
    }
    cout << result;

    return 0;
}
