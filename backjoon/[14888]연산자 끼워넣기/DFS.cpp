//코드 작성자 : https://parkssiss.tistory.com/126
//
//
#include<iostream>
#include<algorithm>
using namespace std;

const int MAX = 1000000001;
int n;
int number[12];
int operators[4];
int maxans = -MAX;
int minans = MAX;

void dfs(int plus, int minus, int mul, int div, int count, int sum) {
	if (count == n) {
		maxans = max(maxans, sum);
		minans = min(minans, sum);
	}
	if (plus > 0)
		dfs(plus - 1, minus, mul, div, count + 1, sum + number[count]);
	if (minus > 0)
		dfs(plus, minus - 1, mul, div, count + 1, sum - number[count]);
	if (mul > 0)
		dfs(plus, minus, mul - 1, div, count + 1, sum * number[count]);
	if (div > 0)
		dfs(plus, minus, mul, div - 1, count + 1, sum / number[count]);
}

int main(void) {
	cin >> n;
	for (int i = 0; i < n; i ++) {
		cin >> number[i];
	}
	for (int i = 0; i < 4; i++) {
		cin >> operators[i];
	}
	dfs(operators[0], operators[1], operators[2], operators[3], 1, number[0]);
	cout << maxans << endl;
	cout << minans << endl;
	return 0;
}
