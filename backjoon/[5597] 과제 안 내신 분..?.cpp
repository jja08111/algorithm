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

    int ok[31] = {false, };
    for (int i = 0; i < 28; ++i) {
        int n;
        cin >> n;
        ok[n] = true;
    }

    int count = 0;
    for (int i = 1; i < 31; ++i) {
        if (!ok[i]) {
            cout << i << endl;
            count++;
            if (count > 2) {
                break;
            }
        }
    }

    return 0;
}
