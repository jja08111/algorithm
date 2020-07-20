# 해결 
입력 값들이 사전 순서대로 주어지는데 이 값들을 방향그래프로 표현하여 위상정렬하면 원하는 알파벳 순서를 얻을 수 있다.  

방향그래프를 만들 때 출력할 단어의 순서가 a-z까지 전부이다. 따라서 26개의 정점을 모두 만들어야 한다.  
두 단어를 비교 할때 같지 않은 문자가 나올 때에 간선에 값을 집어 넣는다. 이때 'a' 값을 빼주어서 0번 인덱스를 a로 표현할 수 있다.  

그래프를 만들고 나서는 DFS 탐색하며 함수가 종료될 때 order에 순서를 추가하면 역순으로 order가 정렬된다.  
다시 역으로 order를 뒤집으면 정렬된 order를 얻을 수 있다.  

순서에 모순을 찾는 방법은 간선들을 정렬된 order 반대 방향으로 연결 되어있는 것을 찾는 것이다.  
```c++
vector<vector<int> > adj;

void makeGraph(const vector<string>& words)
{
	adj = vector<vector<int> >(26, vector<int>(26, 0));
	for (int j = 1;j < words.size();++j)
	{
		int i = j - 1, len = min(words[i].size(), words[j].size());
		for (int k = 0;k < len;++k)
			if (words[i][k] != words[j][k])
			{
				int a = words[i][k] - 'a';
				int b = words[j][k] - 'a';
				adj[a][b] = 1;
				break;
			}
	}
}

vector<int> seen, order;

void dfs(int here)
{
	seen[here] = 1;
	for (int there = 0;there < adj.size();++there)
		if (adj[here][there] && !seen[there])
			dfs(there);
	order.push_back(here);
}

vector<int> topologicalSort()
{
	int m = adj.size();
	seen = vector<int>(m, 0);
	order.clear();

	for (int i = 0;i < m;++i)
		if (!seen[i])
			dfs(i);

	reverse(order.begin(), order.end());

	for (int i = 0;i < m;++i)
		for (int j = i + 1;j < m;++j)
			if (adj[order[j]][order[i]])
				return vector<int>();

	return order;
}
```
