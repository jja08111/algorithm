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

const int MAX = 1000001;

int main(void) {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int tc;
	cin >> tc;
	while (tc--) {
		int k;
		cin >> k;

		multiset<int> s;
		for (int i = 0; i < k; ++i) {
			char oper;
			int n;
			cin >> oper >> n;
			switch (oper)
			{
			case 'I':
				s.insert(n);
				break;
			case 'D':
				if (!s.empty()) {
					s.erase(s.find(n == 1 ? *s.rbegin() : *s.begin()));
				}
				break;
			default:
				break;
			}
		}
		
		if (s.empty()) {
			cout << "EMPTY" << '\n';
		} else {
			cout << *s.rbegin() << ' ' << *s.begin() << '\n';
		}
	}

	return 0;
}
