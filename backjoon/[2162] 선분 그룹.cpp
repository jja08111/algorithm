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

typedef struct DisjointSet{
	vector<int> parent, rank, counter;
	int mergedCount = 0;

	DisjointSet(int n) : parent(n), rank(n, 1), counter(n, 1) {
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}
	int find(int n) {
		if (parent[n] == n)
			return n;
		return parent[n] = find(parent[n]);
	}
	void merge(int a, int b) {
		a = find(a);
		b = find(b);

		if (a == b)
			return;

		mergedCount++;

		if (rank[a] > rank[b])
			swap(a, b);
		parent[a] = b;
		counter[b] += counter[a];
		if (rank[a] == rank[b])
			rank[b]++;
	}
} DisjointSet;

struct vector2 {
	double x, y;

	explicit vector2(double _x = 0, double _y = 0) : x(_x), y(_y) {}
	bool operator < (const vector2& other) const {
		return x != other.x ? x < other.x : y < other.y;
	}
	vector2 operator - (const vector2& other) const {
		return vector2(x - other.x, y - other.y);
	}
	// 벡터의 외적
	double cross(const vector2& other) const {
		return x * other.y - other.x * y;
	}
};

typedef struct {
	vector2 a, b;
} Line;

const int MAX_N = 3001;

int N;
Line lines[MAX_N];

double ccw(vector2 a, vector2 b) {
	return a.cross(b);
}

double ccw(vector2 p, vector2 a, vector2 b) {
	return ccw(a - p, b - p);
}

bool segmentIntersects(
	vector2 a, vector2 b, 
	vector2 c, vector2 d
) 
{
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);

	if (ab == 0 && cd == 0) {
		if (b < a)
			swap(a, b);
		if (d < c)
			swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

int main(void) {
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> lines[i].a.x >> lines[i].a.y >>
		 	lines[i].b.x >> lines[i].b.y;
	}

	DisjointSet set(N);
	for (int i = 0; i < N; ++i) {
		Line& here = lines[i];
		for (int j = i + 1; j < N; ++j) {
			Line& there = lines[j];
			if (segmentIntersects(here.a, here.b, there.a, there.b)) {
				set.merge(i, j);
			}
		}
	}

	cout << N - set.mergedCount << endl;
	int maxCount = 0;
	for (int cnt : set.counter) {
		maxCount = max(maxCount, cnt);
	}
	cout << maxCount;

	return 0;
}


