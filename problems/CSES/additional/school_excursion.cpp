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

/*
Each connected component can be black or white  ==> we want to do subset sum on the vector of components sizes

We calculate the component sizes using DSU

There can't be more than 2 * sqrt(n) different component sizes since they sum to n and
a1 + a2 + ... a_{2 sqrt(n)} >= 1 + 2 + ... + 2 * sqrt(n) = sqrt(n) * (2 sqrt(n) + 1) > n

We let dp[i][j] be 1 iff we can sum to j exactly using only numbers which are <= i 

Then if count[i] is the number of components of size i then
dp[i][j] = OR(k <= j/i)dp[i - 1][j - ik] = is_positive(sum(k <= j/i)dp[i - 1][j - ik])

we can calculate O(i) prefix sums (one for each congruence class) of size O(n / i) in O(n) and then use this to make each transition O(n)

Total complexity: O(N sqrt(N))
*/

struct DSU {
	vector<i64> parent;
	vector<i64> sizes;
	i64 n;

	DSU(i64 n) : n(n){
		parent.resize(n);
		sizes.resize(n);

		iota(parent.begin(), parent.end(), 0);
		sizes.assign(n, 1);
	}

	i64 find(i64 x){
		if (parent[parent[x]] != parent[x]){
			parent[x] = find(parent[x]);
			// parent[x] is now root
		}
		return parent[x];
	}

	bool unite(i64 x, i64 y){
		i64 rx = find(x), ry = find(y);
		if (rx == ry){
			return false;
		}

		// attach rx to ry
		if (sizes[rx] > sizes[ry]){
			swap(rx, ry);
		}
		sizes[ry] += sizes[rx];
		parent[rx] = ry;
		return true;
	}

	void update_sizes(){
		for (i64 x = 0; x < n; x++){
			sizes[x] = sizes[find(x)];
		}
	}
};

// returns vector<vector<i64>> b such that
// b[i][j] = sum(mod < j) a[mod * k + i]
vector<i64> mod_prefix(vector<i64> &a, i64 mod){
	const i64 n = a.size() - 1;
	vector<i64> b(n + mod + 1);
	for (i64 i = 0; i < mod; i++){
		// how many integers k % mod == i in range [0,n] = how many multiples of mod in [0,n-k]
		for (i64 j = 0; j <= (n - i) / mod; j++){
			// accesses at most position (n - i)/mod * mod + mod + i = n + mod
			b[(j + 1) * mod + i] = b[j * mod + i] + a[mod * j + i];
		}
	}
	return b;
}

void solve(){
	i64 n, m;		
	cin >> n >> m;

	DSU dsu(n);
	i64 a, b;
	for (i64 i = 0; i < m; i++){
		cin >> a >> b;
		--a; --b; // 0-indexing
		dsu.unite(a, b);
	}
	dsu.update_sizes();

	vector<i64> cnt(n + 1, 0);
	for (i64 x: dsu.sizes){
		++cnt[x];
	}
	for (i64 i = 1; i <= n; i++){
		cnt[i] /= i;  // each component of size i was counted i times
	}

	// dp[j]: whether it is possible to use numbers up to s from components array to sum up to j
	// where s starts at 0 (so only dp[0] is true)
	vector<i64> dp(n + 1, 0);
	dp[0] = 1;
	for (i64 s = 1; s <= n; s++){
		if (cnt[s] == 0){ // this skip guarantees outer loop runs O(sqrt(N)) times
			continue;
		}
		vector<i64> p = mod_prefix(dp, s);
		for (i64 i = 0; i <= n; i++){
			// sum(0 <= k <= min(count[s], i / s)) dp[i - s * k]
			// Let i = sq + r
			// then target = sum(0 <= k <= q)dp[r + s * k] - sum(0 <= k < max(q - count[s], 0)dp[r + s * k] = p[i % s][i / s + 1] - p[i % s][max(i / s - count[s], 0)]
			// however we flatten this for performance and we represent p[r][k] as p[k * s + r]
			// since k = i/s + 1 so maximum value is floor(n/s + 1) * s + n % s = n + s, the array size should n + s + 1
			i64 back_edges = p[i + s] - p[s * max(i / s - cnt[s], (i64)0) + i % s];
			dp[i] = (back_edges > 0) ? 1 : 0;
		}
	}
	for (i64 i = 1; i <= n; i++){
		cout << dp[i];
	}
	cout << endl;
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
