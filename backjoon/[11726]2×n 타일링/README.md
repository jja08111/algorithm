# 해결 
here 만큼 타일이 남았을 때 몇 가지의 방법으로 타일링을 할 수 있는지를 반환하는 count함수를 만들어 해결했다.  
이때 메모이제이션을 이용하여 중복되는 계산을 없앴다.  

이 문제를 풀때 MOD 연산에 유의해야 한다.  
```c++
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
``
