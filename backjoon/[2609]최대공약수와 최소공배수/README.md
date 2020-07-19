# 해결 
[유클리드 호제법](https://github.com/jja08111/algorithm/tree/master/algospot/14%20%EC%A0%95%EC%88%98%EB%A1%A0/5%20%EC%9C%A0%ED%81%B4%EB%A6%AC%EB%93%9C%20%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98)을 이용하여 해결했다.  
```c++
#include <iostream>
using namespace std;

int getGCD(int a, int b)
{
	if (b == 0)
		return a;
	return getGCD(b, a%b);
}

int main()
{
	int a, b;
	cin >> a >> b;

	int gcd = getGCD(a, b);
	int lcd = a*b / gcd;
	cout << gcd << endl << lcd << endl;

	return 0;
}
```
