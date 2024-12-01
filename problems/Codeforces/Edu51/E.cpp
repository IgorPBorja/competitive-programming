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
	i64 l = 1, r = 0;
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
	vector<int> dp(n, 0); // dp[i] = number of partitions of a[i...n-1] without leading zeroes
	vector<int> suf(n + 1, 0); // suffixed dp

	for (i64 i = n - l.size(); i >= 0; i--){  // a[i..i+l.size()-1] must fit
		if (a[i] == '0') {
			// try to grab a single 0, else no other solution is possible
			if (l[0] == '0'){
				dp[i] = 1;
				suf[i] = (suf[i + 1] + 1) % MOD;
			} else {
				// no partition can be formed from i
				// without multiple leading zeroes
				dp[i] = 0;
				suf[i] = suf[i + 1];
			}
			continue;
		}

		// can grab any a[i..k] with k >= lbound
		// can grab any a[i..k] with k <= rbound
		i64 lbound, rbound;
		if (
			zl[i + l.size()] >= l.size()
		) {
			// total equality: a[i...i+|l|-1] == l[0...|l|-1]
			lbound = i + l.size() - 1;
		} else if (
			zl[i + l.size()] < l.size() && a[i + zl[i + l.size()]] > l[zl[i + l.size()]]
		){
			// strictly larger: a[i...i+|l|-1] > l[0...|l|-1]
			lbound = i + l.size() - 1;
		} else {
			// strictly smaller: a[i...i+|l|-1] < l[0...|l|-1]
			lbound = i + l.size();
		}

		// try to compare a[i..i+|r|] using z-function
		if (i + r.size() > n){
			// all are small
			rbound = n - 1;
		} else if (
			zr[i + r.size()] >= r.size()
		) {
			// total equality: a[i..i+|r|-1] == r[0..|r|-1]
			rbound = i + r.size() - 1;
		} else if (
			zr[i + r.size()] < r.size() && a[i + zr[i + r.size()]] < r[zr[i + r.size()]]
		) {
			// strictly smaller: a[i..i+|r|-1] < r[0..|r|-1]
			rbound = i + r.size() - 1;
		} else {
			// strictly larger: a[i..i+|r|-1] > r[0..|r|-1]
			rbound = i + r.size() - 2;
		}

		// invalid interval: [lbound..rbound] with lbound > rbound
		if (lbound > rbound){
			dp[i] = 0;
			suf[i] = suf[i + 1];
			continue;
		}
		// we can grab any k in lbound...rbound, leaving a[k+1...] to solve
		// => sum(k=lbound..rbound) dp[k + 1] = suf[lbound + 1] - suf[rbound + 2]

		// can't take everything
		if (rbound <= n - 2){
			dp[i] = (suf[lbound + 1] + MOD - suf[rbound + 2]) % MOD;
		} else {
			// the +1 accounts for taking the whole suffix
			dp[i] = (suf[lbound + 1] + 1) % MOD;
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
