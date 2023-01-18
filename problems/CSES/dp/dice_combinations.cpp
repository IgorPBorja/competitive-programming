#include <bits/stdc++.h>
using namespace std;
#define mod (int(1e9) + 7)

int dicesum(int m, int dp[], int sum)
{
	if (sum == 0)
	{
		return 1; // the empty sum (base case!)
	}
	if (dp[sum] != 0)
	{
		return dp[sum];
	}
	else
	{
		for (int i = 1; i <= min(sum, m); i++)
		{
			dp[sum] = ((dp[sum] % mod) +
					   (dicesum(m, dp, sum - i) % mod)) %
					  mod;
		}
		return dp[sum];
	}
}

int main()
{
	int n;
	cin >> n;
	int dp[n + 1]; // 0 to n
	for (int i = 0; i < n + 1; i++)
	{
		dp[i] = 0;
	}
	cout << dicesum(6, dp, n);
}
