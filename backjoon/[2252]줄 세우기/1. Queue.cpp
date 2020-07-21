#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int n, m;
vector<vector<int> > adj;
vector<int> indegree;

void makeGraph()
{
	adj = vector<vector<int> >(n + 1, vector<int>());
	indegree = vector<int>(n + 1, 0);
	for (int i = 0;i < m;++i)
	{
		int a, b;
		cin >> a >> b;
		++indegree[b];
		adj[a].push_back(b);
	}
}

void printTopological()
{
	queue<int> q;
	for (int i = 1;i <= n;++i)
		if (!indegree[i])
			q.push(i);

	while (!q.empty())
	{
		int here = q.front();
		q.pop();

		cout << here << ' ';

		for (int i = 0;i < adj[here].size();++i)
		{
			int there = adj[here][i];
			--indegree[there];
			if (!indegree[there])
				q.push(there);
		}
	}
}

int main()
{
	cin >> n >> m;
	
	makeGraph();
	printTopological();

	return 0;
}
