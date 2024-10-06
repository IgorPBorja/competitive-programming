// #define TESTCASES
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

void solve(){
	i64 n, a, b;
	cin >> n >> a >> b;

	vector<i64> u, v;
	i64 x;
	for (i64 i = 0; i < n / 2; i++){
		cin >> x;
		u.emplace_back(x);
	}
	for (i64 i = n / 2; i < n; i++){
		cin >> x;
		v.emplace_back(x);
	}

	vector<i64> sums_u, sums_v;
	const i64 m1 = u.size(), m2 = v.size();
	for (i64 mask = 0; mask < (1ll << m1); mask++){
		i64 s = 0;
		for (i64 i = 0; i < m1; i++){
			if (mask & (1ll << i)){
				s += u[i];
			}
		}
		sums_u.emplace_back(s);
	}
	for (i64 mask = 0; mask < (1ll << m2); mask++){
		i64 s = 0;
		for (i64 i = 0; i < m2; i++){
			if (mask & (1ll << i)){
				s += v[i];
			}
		}
		sums_v.emplace_back(s);
	}

	sort(sums_u.begin(), sums_u.end());
	sort(sums_v.begin(), sums_v.end());

	i64 cnt = 0;
	for (i64 x: sums_u){
		auto l_it = lower_bound(sums_v.begin(), sums_v.end(), a - x);
		auto r_it = upper_bound(sums_v.begin(), sums_v.end(), b - x);
		cnt += r_it - l_it;
	}
	cout << cnt << endl;
}
 
signed main(){
	fastio;
#ifdef DEBUG
	freopen("/tmp/in", "r", stdin);
#endif
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
