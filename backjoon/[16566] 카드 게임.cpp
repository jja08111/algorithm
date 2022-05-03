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

struct DisjointSet {
	vector<int> parent;
	DisjointSet(int size) : parent(size) {
		for (int i = 0; i < size; ++i) {
			parent[i] = i;
		}
	}
	int find(int n) {
		if (n == parent[n])
			return parent[n];
		return parent[n] = find(parent[n]);
	}
	void merge(int a, int b) {
		a = find(a), b = find(b);
		if (a == b)
			return;
		parent[a] = b;
	}
};

const int MAX_M = 4000001;

int N, M, K;

int main(void) {
	ios_base::sync_with_stdio(0); cin.tie(0);

	vector<int> s;
	vector<int> enemy;

	cin >> N >> M >> K;
	for (int i = 0; i < M; ++i) {
		int n;
		cin >> n;
		s.push_back(n);
	}
	sort(s.begin(), s.end());

	for (int i = 0; i < K; ++i) {
		int n;
		cin >> n;
		enemy.push_back(n);
	}

	vector<int> ret;
	DisjointSet usedSet(M);

	for (int n : enemy) {
		auto upper = upper_bound(s.begin(), s.end(), n);
		int index = upper - s.begin();
		
		index = usedSet.find(index);

		int picked = s[index];
		usedSet.merge(index, index + 1);
		ret.push_back(picked);
	}

	for (auto n : ret) {
		cout << n << '\n';
	}

	return 0;
}
