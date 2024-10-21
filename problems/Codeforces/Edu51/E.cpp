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
 
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define print(first, last) for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define printgraph(msg, G) cout << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

const i64 MOD = 998244353;

vector<i64> zfunc(string &s){
	const i64 n = s.size();
	vector<i64> z(n);
	z[0] = n;
	i64 l = 0, r = -1;
	for (i64 i = 1; i < n; i++){
		// limit z by going up to r, or less if z[i-l] limits it
		z[i] = max((i64)0, min(z[i - l], r - i + 1));
		// try to expand (resetting l to i)
		while (z[i] < n - i && s[i + z[i]] == s[z[i]]){
			l = i;
			r = i + z[i];  // from i + z[i] - 1 to i + z[i]
			z[i]++;
		}
	}
	return z;
}

void solve(){
	string a, l, r;
	cin >> a >> l >> r;

	string lcomp = l + a, rcomp = r + a;
	vector<i64> zl = zfunc(lcomp), zr = zfunc(rcomp);

	const i64 n = a.size();
	i64 dp[n];  // dp[i] = number of partitions of a[0..i] without leading zeroes
	i64 suf[n + 1]; // suffixed dp
	suf[n] = 0;

	vector<i64> skip(n + 1); // if 0, skips to next character not zero
	iota(skip.begin(), skip.end(), 0);
	// O(2 * N) -> two passes
	for (i64 i = 0; i < n; i++){
		if (a[i] == '0' && (i + 1 >= n || a[i + 1] != '0')){
			for (i64 j = i; j >= 0 && a[j] == '0'; j--){
				skip[j] = i + 1;
			}
		}
	}

	for (i64 i = n - 1; i >= 0; i--){
		i64 j = skip[i];
		// try to compare a[j..j+|l|] with l using z-function

		// try to grab a single 0
		// TODO will this be double counted?
		if (l.size() == 1 && l[0] == '0' && j > i){
			if (i + 1 < n){
				dp[i] = dp[i + 1];
			} else {
				dp[i] = 1;
			}
		} else {
			dp[i] = 0;
		}

		// can grab any a[i..k] with k >= lbound
		// can grab any a[i..k] with k <= rbound
		i64 lbound, rbound;
		if (j + l.size() > n){
			// no partition will be large enough
			suf[i] = (suf[i + 1] + dp[i]) % MOD;
			continue;
		} else if (
			zl[j + l.size()] >= l.size()
		) {
			// total equality
			lbound = j + l.size() - 1;
		} else if (
			zl[j + l.size()] < l.size() && a[j + zl[j + l.size()]] > l[zl[j + l.size()]]
		){
			// strictly larger
			lbound = j + l.size() - 1;
		} else {
			lbound = j + l.size();
		}

		// try to compare a[j..j+|r|] using z-function
		if (j + r.size() > n){
			// all are small
			rbound = n - 1;
		} else if (
			zr[j + l.size()] >= r.size()
		) {
			// total equality
			rbound = j + r.size() - 1;
		} else if (
			zr[j + r.size()] < r.size() && a[j + zr[j + r.size()]] < r[zr[j + r.size()]]
		) {
			// strictly smaller
			rbound = j + r.size() - 1;
		} else {
			rbound = j + r.size() - 2;
		}

		// valid interval: [lbound..rbound]
		if (lbound > rbound){
			suf[i] = (suf[i + 1] + dp[i]) % MOD;
			continue;
		}

		// we deal with taking k=n-1 (everything) as a corner case
		// the case lbound == rbound == n - 1
		// cerr << "i=" << i << " lbound=" << lbound << " rbound=" << rbound << endl;
		if (lbound <= n - 1 && n - 1 <= rbound){
			dp[i] = (dp[i] + 1) % MOD;
		}
		rbound = min(rbound, n - 2);

		// we can grab any k in lbound...rbound, leaving a[k+1...] to solve
		// => sum(k=lbound..rbound) dp[k + 1] = suf[lbound + 1] - suf[rbound + 2]
		if (lbound <= rbound){
			dp[i] = (dp[i] + suf[lbound + 1] + MOD - suf[rbound + 2]) % MOD;
		}
		suf[i] = (suf[i + 1] + dp[i]) % MOD;
	}
	// printmsg("dp=", dp, dp + n);
	// printmsg("suf=", suf, suf + n + 1);
	cout << dp[0] << endl;
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
