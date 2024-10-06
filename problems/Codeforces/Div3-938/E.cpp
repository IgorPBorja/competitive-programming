#define TESTCASES
// #define MYDEBUG
 
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

bool ok(vector<i64>& b, i64 k){
	const i64 n = b.size();
	bool ans = true;
	vector<i64> a(n), p(n + 1);
	p[0] = 0;
	for (i64 i = 0; i + k - 1 < n; i++){
		// inverted p[i] - p[max(i - k + 1, (i64)0)] times
		// must invert (1 - (b[i] + p[i])) times
		i64 prev_flips = (p[i] + p[max(i - k + 1, (i64)0)]) % 2;
		a[i] = (1 + b[i] + prev_flips) % 2;
		p[i + 1] = (p[i] + a[i]) % 2;
	}
	for (i64 i = n - k + 1; i < n; i++){
		p[i + 1] = p[i];
	}
	for (i64 i = n - k + 1; i < n; i++){
		// can't be start of flip
		i64 prev_flip = (p[i] + p[max(i - k + 1, (i64)0)]) % 2;
		ans = ans && (prev_flip == (1 - b[i]));
	}
	return ans;
}

void solve(){
	i64 n;
	string s;
	cin >> n >> s;

	vector<i64> b(n);
	for (i64 i = 0; i < n; i++) b[i] = s[i] - '0';
	for (i64 k = n; k >= 1; k--){
		if (ok(b, k)){
			cout << k << endl;
			return;
		}
	}
	cout << 1 << endl;
}
 
signed main(){
	fastio;
// #ifdef MYDEBUG
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
