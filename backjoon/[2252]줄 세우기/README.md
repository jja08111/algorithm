# 해결 
처음에는 키가 큰 학생에서 작은 학생으로 방향 그래프를 만들어 DFS탐색을 하며 정렬한 결과를 출력했다.  
```c++
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
```
하지만 이러한 방법은 너무 느리고 메모리도 엄청 차지했다.  

다른 방법으로는 다른 곳에서 현재 정점으로 향하는 간선의 수를 표현하는 차수를 도입하는 것이다.  
큐를 이용해 차수가 0 일때 출력하고 다음 정점으로 넘어가고, 아니면 하나씩 차수를 줄여가는 방식이다.   
이 방법을 이용하니 속도, 메모리 둘 다 향상되었다.  
```c++
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
```
