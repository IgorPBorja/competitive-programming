#define TESTCASES
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

const i64 INF = (i64)2e18;

i64 score(bool s[], i64 n, i64 k){
	i64 free = 0;
	i64 cost = (n * (n + 1)) / 2;
	bool should_be_free[n];
	fill(should_be_free, should_be_free + n, false);
	for (i64 i = n - 1; i > 0 && free < k; i--){  // can't get discount on first day
		if (!s[i]) continue;
		should_be_free[i] = true;
		cost -= i + 1;
		++free;
	}
	if (free < k) return INF;
	i64 pref_free[n];
	pref_free[0] = 0;   // first one can't be free
	for (i64 i = 1; i < n; i++){
		pref_free[i] = pref_free[i - 1] + should_be_free[i];
		if (2 * pref_free[i] > i + 1){
			// can't find a pair for each free item
			return INF;
		}
	}
	return cost;
}

void solve(){
	i64 n;
	cin >> n;
	string _s;
	cin >> _s;
	bool s[n];
	for (i64 i = 0; i < n; i++){
		s[i] = _s[i] == '1';
	}

	if (n == 1){
		cout << 1 << endl;
		return;
	}
	
	i64 l = 0, r = n;
	i64 ans = INF;
	while (l <= r){
		const i64 mid = l + (r - l) / 2;
		i64 cost = score(s, n, mid);
		if (cost < INF){
			ans = cost;
			l = mid + 1;
		} else {
			r = mid - 1;
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
