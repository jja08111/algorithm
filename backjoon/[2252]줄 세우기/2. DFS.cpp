#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<vector<bool> > adj;

void makeGraph()
{
	adj = vector<vector<bool> >(n, vector<bool>(n, false));
	for (int i = 0;i < m;++i)
	{
		int a, b;
		cin >> a >> b;
		adj[a-1][b-1] = true;
	}
}

vector<bool> seen;
vector<int> order;

void dfs(int here)
{
	seen[here] = true;
	for (int there = 0;there < n;++there)
		if (adj[here][there] && !seen[there])
			dfs(there);
	order.push_back(here + 1);
}

vector<int> topological()
{
	seen = vector<bool>(n, false);
	order.clear();

	for (int i = 0;i < n;++i)
		if (!seen[i])
			dfs(i);

	reverse(order.begin(), order.end());

	return order;
}

int main()
{
	cin >> n >> m;
	
	makeGraph();
	vector<int> ret = topological();

	for (int i = 0;i < n;++i)
		cout << ret[i] << ' ';

	return 0;
}
