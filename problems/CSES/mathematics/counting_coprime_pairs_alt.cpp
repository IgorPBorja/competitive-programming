//
// Created by igor-borja on 7/11/24.
//
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

#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define print(first, last) for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };

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

// FIXME:
const i64 MAX_N = 1e6 + 3;

unordered_map<i64, vector<i64>> sieve(const vector<i64>& cnt){
	unordered_map<i64, vector<i64>> primes;
	vector<i64> is_prime(MAX_N + 1, 1);
	for (i64 i = 2; i <= MAX_N; i++){
		if (!is_prime[i]) continue;
		if (cnt[i]){
			primes[i].emplace_back(i);
		}
		for (i64 j = 2 * i; j <= MAX_N; j += i){
			is_prime[j] = false;
			if (cnt[j]){
				primes[j].emplace_back(i);
			}
		}
	}
	return primes;
}

void solve(){
	i64 n;
	cin >> n;
	vector<i64> a(n);
	vector<i64> cnt(MAX_N + 1, 0);
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
		++cnt[a[i]];
	}
	const unordered_map<i64, vector<i64>> primes = sieve(cnt);
	vector<i64> mult(MAX_N + 1, 0);

	// consider all submasks of the number in O(p(M) * 2^p(M)) where
	// p is the inverse primorial (in practice p(10^6) = 7)
	i64 ans = (cnt[1] * (cnt[1] - 1)) / 2;
	mult[1] = cnt[1];
	for (i64 i = 2; i <= MAX_N; i++){
		if (cnt[i] == 0) continue;
		const vector<i64> pdiv = primes.at(i);
		const i64 w = pdiv.size();
		for (i64 mask = 0; mask < (1ll << w); mask++){
			i64 mapped_mask = 1;
			for (i64 j = 0; j < w; j++){
				if ((mask >> j) & 1){
					mapped_mask *= pdiv[j];
				}
			}
			// consider possible pairs (with inclusion exclusion)
			// starts by removing mult[p_j1], then adding mult[p_j1, p_j2], ...
			i64 sign = -2 * (__builtin_popcount(mask) % 2) + 1;
			ans += sign * cnt[i] * mult[mapped_mask];
			// add contribution given by a[i]
			mult[mapped_mask] += cnt[i];
		}
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

