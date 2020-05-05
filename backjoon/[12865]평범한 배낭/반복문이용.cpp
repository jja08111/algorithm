// 출처 : https://www.acmicpc.net/user/wlsth1004100

#include<cstdio>
#include<algorithm>
#include<string.h>
#include<vector>

using namespace std;

const int MAX_N = 100;
const int MAX_W = 100010;

int dp[100];
int N, K;
pair<int,int> item[100001];
int main()
{
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &item[i].first, &item[i].second);

		for (int j = K; j >= item[i].first; j--)
			dp[j] = max(dp[j], dp[j - item[i].first] + item[i].second);
	}

	printf("%d", dp[K]);
	return 0;
}
