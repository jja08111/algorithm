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

int K;
string str;

bool checkPossible(string str) {
    if (str.size() == 1)
        return false;
    if (str.size() == 2 && str[1] == '0')
        return false;
    return true;
}

int solve() {
    queue<pair<string, int> > q;
    set<string> discovered;
    int prevOrder = 0;
    int ret = 0;
    q.push({str, 0});

    while (!q.empty()) {
        string cand = q.front().first;
        int order = q.front().second;
        q.pop();

        if (prevOrder != order) {
            prevOrder = order;
            discovered.clear();
        }
        if (order == K) {
            ret = max(ret, stoi(cand));
            continue;
        }

        for (int i = 0; i < str.size() - 1; ++i) {
            for (int j = i + 1; j < str.size(); ++j) {
                if (i == 0 && str[j] == '0')
                    continue;

                swap(cand[i], cand[j]);
                if (discovered.find(cand) == discovered.end()) {
                    q.push({cand, order + 1});
                    discovered.insert(cand);
                }
                swap(cand[i], cand[j]);
            }
        } 
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> str >> K;

    if (!checkPossible(str)) {
        cout << -1;
        return 0;
    }

    cout << solve() << endl;

    return 0;
}
