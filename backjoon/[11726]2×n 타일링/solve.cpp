#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MOD = 10007;

int cache[1001];

int count(int here)
{
	if (here < 0)
		return 0;
	if (here == 0)
		return 1;

	int& ret = cache[here];
	if (ret != -1)
		return ret;

	ret = count(here - 1) % MOD;
	ret = (ret + count(here - 2)) % MOD;
	return ret;
}

int main()
{
	int n;
	cin >> n;

	memset(cache, -1, sizeof(cache));
	cout << count(n) << endl;

	return 0;
}
