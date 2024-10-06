#include <unordered_map>
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
#define i32 int32_t
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

vector<i64> primes;
const i64 MAX_N = (i64)1e6;
i64 global_factors[(i64)1e6 + 1][20];
i64 distinct[(i64)1e6 + 1];

void get_primes(){
	i64 is_composite[MAX_N + 1];
	fill(is_composite, is_composite + MAX_N + 1, 0);
	fill(distinct, distinct + MAX_N + 1, 0);
	is_composite[0] = 1, is_composite[1] = 1;
	for (i64 i = 2; i <= MAX_N; i++){
		if (is_composite[i]) continue;
		primes.emplace_back(i);
		global_factors[i][0] = i;
		distinct[i] = 1;
		for (i64 j = 2 * i; j <= MAX_N; j += i){
			is_composite[j] = true;
			global_factors[j][distinct[j]] = i;
			++distinct[j];
		}
	}
	sort(primes.begin(), primes.end());
}

unordered_map<i64, vector<i64>> factor_array(const vector<i64> &a){
	unordered_map<i64, vector<i64>> a_primes;
	for (i64 i = 0; i < a.size(); i++){
		i64 x = a[i];	
		for (i64 j = 0; j < distinct[x]; j++){
			a_primes[global_factors[x][j]].emplace_back(i);
		}
	}
	return a_primes;
}

struct DSU {
	vector<i64> p, sz, max_v, min_v;
	i64 components;

	DSU(i64 n) : components(n) {
		p.resize(n);
		max_v.resize(n);
		min_v.resize(n);
		iota(p.begin(), p.end(), 0);
		iota(max_v.begin(), max_v.end(), 0);
		iota(min_v.begin(), min_v.end(), 0);
		sz.assign(n, 1);
	}

	i64 find(i64 x){
		if (p[x] != x) p[x] = find(p[x]);
		return p[x];
	}

	void merge(i64 x, i64 y){
		x = find(x), y = find(y);
		if (x == y) return;
		if (sz[x] > sz[y]) swap(x, y);
		p[x] = y;
		sz[y] += sz[x];
		max_v[y] = max(max_v[y], max_v[x]);
		min_v[y] = min(min_v[y], min_v[x]);
		--components;
	}
};


void solve(){
	i64 n, k;
	cin >> n >> k;
	vector<i64> a(2 * n - 1);

	i64 ones_cnt = 0;
	cin >> a[n - 1];
	if (a[n - 1] == 1) ++ones_cnt;
	for (i64 i = 1; i < n; i++){
		cin >> a[n - 1 + i];
		if (a[n - 1 + i] == 1){
			++ones_cnt;
		}
		a[i - 1] = a[n - 1 + i];
	}

	DSU dsu(2 * n);
	auto factoring = factor_array(a);
	// for (auto[x, y]: factoring) { 
	// 	printmsg("for prime=" << x << " we have pos=", y.begin(), y.end());
	// }

	for (auto[p, positions]: factoring){
		// printmsg("for prime p=" << p << " we have idxs=", idxs.begin(), idxs.end());
		for (i64 i = 0; i < positions.size(); i++){
			i64 x = positions[i], y = positions[(i + 1) % positions.size()];
			if (abs(x - y) <= k){
				dsu.merge(x, y);
			}
		}
	}
	i64 ans = 0;
	for (i64 i = 0; i < 2 * n - 1; i++){
		if ((dsu.p[i] != i) || a[i] == 1) continue;
		++ans;
	}
	cout << ans + ones_cnt * n << endl;
}
 
signed main(){
	get_primes();
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
