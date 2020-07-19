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
		// 연산자를 입력받는다.
		oper = (char)getchar();
		// 입력이 종료된 경우
		if (oper == '\n')
			break;

		if (oper == '-')
			dir = -1;
		// 숫자를 입력받는다.
		scanf("%d", &num);
		ret += dir*num;
	}
	cout << ret << endl;

	return 0;
}
