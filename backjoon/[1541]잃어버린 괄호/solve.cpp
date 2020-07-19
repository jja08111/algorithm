#include <iostream>

using namespace std;

int main()
{
	int num, ret, dir = 1;
	char oper;

	cin >> num;

	ret = num;
	while (true)
	{
		oper = (char)getchar();
		if (oper == '\n')
			break;
		if (oper == '-')
			dir = -1;
		scanf("%d", &num);
		ret += dir*num;
	}
	cout << ret << endl;

	return 0;
}
