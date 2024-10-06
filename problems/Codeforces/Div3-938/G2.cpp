#define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vvi vector<vector<int>>
#define vvb vector<vector<bool>>
#define vvc vector<vector<char>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define eb emplace_back
#define ep emplace
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
 
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

const i64 INF = 1e18;

i64 gcd(i64 a, i64 b){
	i64 tmp;
	while (a > 0 && b > 0){
		tmp = max(a, b);
		a = min(a, b);
		b = tmp % a;
	}
	return max(a, b);
}

bool valid(i64 x, i64 y, i64 n, i64 m){
	return (0 <= x && x < n && 0 <= y && y < m);
}

void solve(){
	i64 n, m;	
	cin >> n >> m;
	vector<vector<i64>> grid(n, vector<i64>(m));
	for (i64 i = 0; i < n; i++){
		for (i64 j = 0; j < m; j++){
			cin >> grid[i][j];
		}
	}
	vector<vector<set<i64>>> v(n, vector<set<i64>>(m));
	for (i64 i = 1; i * i <= grid[0][0]; i++){
		if (grid[0][0] % i == 0){
			v[0][0].insert(i);
			if (i != grid[0][0] / i){
				v[0][0].insert(grid[0][0] / i);
			}
		}
	}
	for (i64 i = 0; i < n; i++){
		for (i64 j = 0; j < m; j++){
		}
	}
}
 
signed main(){
	fastio;
// #ifdef DEBUG
// 	freopen("/tmp/in", "r", stdin);
// #endif
	int t;
#ifdef TESTCASES
	cin >> t;
#else
	t = 1;
#endif
	while (t--){
		solve();
	}
}
