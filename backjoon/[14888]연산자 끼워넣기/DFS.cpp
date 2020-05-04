#include<iostream>
#include<algorithm>
using namespace std;

const int INF = 987654321;
int n,number[11],operators[4];
int maxRet = -INF;
int minRet = INF;

void dfs(int index, int sum) 
{
	if (index == n) 
	{
		maxRet = max(maxRet, sum);
		minRet = min(minRet, sum); 
	}
	
	for(int i=0;i<4;++i)
        if(operators[i]>0)
        {
            --operators[i];
            switch(i)
            {
                case 0: dfs(index+1,sum+number[index]); break;
                case 1: dfs(index+1,sum-number[index]); break;
                case 2: dfs(index+1,sum*number[index]); break;
            	case 3: dfs(index+1,sum/number[index]); break;
            }
            ++operators[i];
        }
}

int main(void)
{
	cin >> n;
	for (int i = 0; i < n; i ++)
		cin >> number[i];
	for (int i = 0; i < 4; i++)
		cin >> operators[i];
		
	dfs(1, number[0]);
	cout << maxRet << endl;
	cout << minRet << endl;
	return 0;
}
