# 해결 
마이너스 연산자가 나오는 순간 그 뒤에는 적절히 괄호 처리하여 전부 음수 값으로 만들 수 있다.  
이러한 부분을 이용하여 해결했다.  

유의할 부분은 입력의 마지막 값이 EOF 이 아닌 \n 인 것이다.
```c++
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
```
