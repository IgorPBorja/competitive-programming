// #define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
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

// sort by equivalence classes
void csort(
	vector<i64>& p, // p[i]: start of ith suffix in sorted order
	const vector<i64>& c, // 
	i64 offset
){
	const i64 n = p.size();
	const i64 sz = max((i64)300, n);
	i64 endpoint[sz];  // class endpoints
	fill(endpoint, endpoint + sz, 0);
	for (i64 x: c){
		++endpoint[x];
	}
	// pref
	for (i64 i = 1; i < sz; i++){
		endpoint[i] += endpoint[i - 1];
	}
	vector<i64> newp(n);
	// iterate backwards put elements in backwards class order
	// (class of position of ith suffix + offset)
	// (so last elements of same class come last --> stable)
	for (i64 i = n - 1; i >= 0; i--){
		i64 cls = c[(p[i] + offset) % n];
		newp[--endpoint[cls]] = p[i];
	}
	swap(newp, p);
}

template<typename Container>
pair<vector<i64>, vector<vector<i64>>> suffix_array(Container a){
	const i64 n = a.size();
	// calculate exactly what we will need which is max(2^k: 2^k < 2 * n)
	// = 1 + max(2^k: 2^k < n) = 1 + floor(log(n-1))
	i64 logn = 1;
	i64 _n = n - 1;
	while (_n > 1){
		++logn;
		_n >>= 1;
	}
	vector<i64> p(n);
	iota(p.begin(), p.end(), 0ll);
	vector<vector<i64>> c(logn + 1, vector<i64>(n));
	for (i64 i = 0; i < n; i++){
		c[0][i] = a[i];
	}
	// sort by first char
	csort(p, c[0], 0);
	// sort by first m=2^k chars (k is a power of 2)
	for (i64 k = 1, m = 2; m < 2 * n; k++, m <<= 1){
		// stable sort by offset
		csort(p, c[k - 1], m >> 1);
		// stable sort by first char
		csort(p, c[k - 1], 0);
		// rebuild new equivalence classes for 2^k group
		c[k][p[0]] = 0;
		i64 cls = 0;
		for (i64 i = 1; i < n; i++){
			// is strict jump between 2^k group at p[i-1] and 2^k group at p[i]?
			if (
				make_pair(c[k-1][p[i-1]], c[k-1][(p[i-1]+m/2) % n])
				< make_pair(c[k-1][p[i]], c[k-1][(p[i]+m/2) % n])
			){
				++cls;
			}
			c[k][p[i]] = cls;
		}
	}
	return {p, c};
}

i64 lcp(
	i64 i, i64 j,
	const vector<vector<i64>>& c
){
	i64 k = c.size();  // for i=0..k-1 c[i] is class of size 2^i
	const i64 n = c[0].size();
	i64 ans = 0;
	for (i64 l = k - 1; l >= 0; l--){
		if (c[l][i] == c[l][j]){
			i = (i + (1ll << l)) % n;
			j = (j + (1ll << l)) % n;
			ans += 1ll << l;
		}
	}
	return ans;
}

vector<i64> lcp_array(
	const vector<i64>& p,
	const vector<vector<i64>>& c
){
	const i64 n = p.size();
	vector<i64> arr(n - 1);
	for (i64 i = 0; i < n - 1; i++){  // skip EOF/sentinel which is always p[0]
		arr[i] = lcp(p[i + 1], p[i], c);
	}
	return arr;
}

void solve(){
	// each substring s is a prefix of a suffix
	// if suffix i has lcp k with suffix i-1 (in sorted order)
	// then it only adds (n-i)-lcp new prefixes (all after the lcp first chars)
	string s;
	cin >> s;
	auto[p, c] = suffix_array(s + "$");
	vector<i64> arr = lcp_array(p, c);
	const i64 n = s.size();
	i64 ans = 0;
	for (i64 i = 0; i < n; i++){
		ans += n - p[i + 1] - arr[i];
	}
	cout << ans << endl;
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
