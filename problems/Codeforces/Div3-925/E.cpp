#define TESTCASES
#define MYDEBUG
 
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

i64 vp(i64 n, i64 p){
	i64 cnt = 0;
	while (n > 0 && n % p == 0){
		n /= p;
		++cnt;
	}
	return cnt;
}

i64 len(i64 n, i64 p){
	i64 cnt = 0;
	while (n >= 1){
		n /= p;
		++cnt;
	}
	return cnt;
}

void solve(){
	i64 n, m;
	cin >> n >> m;

	i64 a[n], v10[n];
	i64 tot = 0;
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
		v10[i] = vp(a[i], (i64)10);
		tot += len(a[i], (i64)10);
	}

	sort(v10, v10 + n);
	reverse(v10, v10 + n);
	for (i64 i = 0; i < n; i += 2){
		tot -= v10[i];
	}

	if (tot >= m + 1){
		cout << "Sasha" << endl;
	} else {
		cout << "Anna" << endl;
	}
}
 
signed main(){
	fastio;
#ifdef MYDEBUG
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
