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

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(0);

    string str;
    string bomb;
    cin >> str >> bomb;

    vector<char> v;
    for (char ch : str) {
        v.push_back(ch);

        if (v.size() >= bomb.size()) {
            bool canBeBomb = true;
            for (int i = 0; i < bomb.size(); ++i) {
                if (bomb[i] != v[v.size() - bomb.size() + i]) {
                    canBeBomb = false;
                    break;
                }
            }
            if (canBeBomb) {
                for (int i = 0; i < bomb.size(); ++i){
                    v.pop_back();
                }
            }
        }
    }

    if (v.empty()) {
        cout << "FRULA";
        return 0;
    }
    for (char ch: v) {
        cout << ch;
    }

    return 0;
}
