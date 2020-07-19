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
