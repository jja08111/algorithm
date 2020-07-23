# 해결 
이 문제를 그래프로 표현하려고 처음에는 각 단어를 정점으로 설정하고 오일러 트레일 혹은 서킷인지 확인하여 해결하려 했다.  
하지만 이러한 방법으로는 100가지의 정점을 만들고 모든 정점을 방문하는 조합을 만들기에는 너무 느려 적용할 수 없다.  

이 문제를 해결하는 방법은 각 단어를 정점이 아닌 간선으로 설정하는 것이다.  
그 후 오일러 서킷인지 확인하는 방법을 이용하여 문제를 해결하면 되는데 오일러 서킷은 흔히 한 붓 그리기를 생각하면 된다.  
오일러 트레일은 한 붓 그리기를 하는데 시작점과 도착점이 다른 것이다.  
```c++
vector<vector<int> > adj;
vector<string> graph[26][26];
vector<int> indegree, outdegree;

void makeGraph(const vector<string>& words)
{
	for (int i = 0;i < 26;++i)
		for (int j = 0;j < 26;++j)
			graph[i][j].clear();

	adj = vector<vector<int> >(26, vector<int>(26, 0));
	indegree = outdegree = vector<int>(26, 0);

	for (int i = 0;i < words.size();++i)
	{
		int a = words[i].front() - 'a';
		int b = words[i].back() - 'a';
		graph[a][b].push_back(words[i]);
		adj[a][b]++;
		outdegree[a]++;
		indegree[b]++;
	}
}
```

무향 그래프에서 오일러 서킷인지 확인하는 방법은 각 정점의 간선이 짝수개여야 한다는 것이다.  
이 문제에서는 방향이 있는 그래프이기 때문에 각 정점으로 들어오가 나가는 간선의 차수를 만들어야 한다.  
이 두 개의 차이가 1보다 초과하면 오일러 서킷 혹은 트레일이 안된다.   
```c++
bool checkEuler()
{
	int plus1 = 0, minus1 = 0;
	for (int i = 0;i < 26;++i)
	{
		int delta = outdegree[i] - indegree[i];
		if (delta < -1 || 1 < delta)
			return false;
		if (delta == 1)
			plus1++;
		if (delta == -1)
			minus1++;
	}
	return (plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0);
}
```

이제 서킷을 형성해야 하는데 우선 오일러 트레일이 있는지 확인한다. 확인 시 간선이 하나는 연결되어 있는 정점으로 시작해야 한다.
이때 깊이 우선 탐색을 하며 간선을 하나씩 지우면서 서킷을 형성한다.  
그리고 없다면 오일러 서킷을 확인한다. 이 서킷들은 모든 간선을 지나야 한다.   
```c++
void getEulerCircuit(int here, vector<int>& circuit)
{
	for (int there = 0;there < adj.size();++there)
	{
		while (adj[here][there] > 0)
		{
			adj[here][there]--;
			getEulerCircuit(there, circuit);
		}
	}
	circuit.push_back(here);
}

vector<int> getEulerTrailOrCircuit()
{
	vector<int> circuit;
	for (int i = 0;i < 26;++i)
	{
		if (outdegree[i] == indegree[i] + 1)
		{
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}
	for (int i = 0;i < 26;++i)
	{
		if (outdegree[i])
		{
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}
	return circuit;
}
```

서킷을 형성하면 DFS과정에서 역으로 단어들을 추가했기 때문에 reverse해줘야 한다.  
그 후 문자열을 만들면 된다.  
```c++
string solve(const vector<string>& words)
{
	makeGraph(words);
	if (!checkEuler())
		return "IMPOSSIBLE";

	vector<int> circuit = getEulerTrailOrCircuit();
	if (circuit.size() != words.size() + 1)
		return "IMPOSSIBLE";

	reverse(circuit.begin(), circuit.end());

	string ret;
	for (int i = 1;i < circuit.size();++i)
	{
		int a = circuit[i - 1], b = circuit[i];
		if (ret.size())
			ret += " ";
		ret += graph[a][b].back();
		graph[a][b].pop_back();
	}
	return ret;
}
```
