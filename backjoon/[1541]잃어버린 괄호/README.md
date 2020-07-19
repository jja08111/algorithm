# 해결 
마이너스 연산자가 나오는 순간 그 뒤에는 적절히 괄호 처리하여 전부 음수 값으로 만들 수 있다.  
이러한 부분을 이용하여 해결했다.  

유의할 부분은 입력의 마지막 값이 EOF 이 아닌 \n 인 것이다.  
따라서 scnaf()로 문자를 입력 받으면 \n 이전까지 입력 받기 때문에 getchar()을 이용하여 연산자를 입력 받았다.
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
		// 연산자를 입력 받는다.
		oper = (char)getchar();
		// 입력이 종료된 경우
		if (oper == '\n')
			break;

		if (oper == '-')
			dir = -1;
		// 숫자를 입력 받는다.
		scanf("%d", &num);
		ret += dir*num;
	}
	cout << ret << endl;

	return 0;
}
```
