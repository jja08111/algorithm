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

bool hasPattern(string s, int index) {
    if (index == s.size()) {
        return true;
    }
    // 앞에부분
    if (index + 4 - 1 < s.size() && s.substr(index, 3) == "100") {
        int j;
        for (j = 3 + index; j + 1 < s.size(); ++j) {
            if (s[j] != '0')
                break;
        }
        for (; j < s.size(); ++j) {
            if (s[j] == '1') {
                if (hasPattern(s, j + 1)) {
                    return true;
                }
            }
            else {
                break;
            }
        }
    }
    // 뒤에부분
    if (index + 2 - 1 < s.size() && s.substr(index, 2) == "01") {
        if (hasPattern(s, index + 2)) {
            return true;
        }
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        string s;
        cin >> s;

        cout << (hasPattern(s, 0) ? "YES" : "NO") << endl;
    }

    return 0;
}
