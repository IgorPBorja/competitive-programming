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

void solve(){
	i64 n;
	cin >> n;
	vector<vector<i64>> a(n, vector<i64>(n));

	for (i64 i = 0; i < n; i++){
		string row;
		cin >> row;
		for (i64 j = 0; j < n; j++){
			a[i][j] = row[j] - '0';
		}
	}

	i64 maxm = 0;
	for (i64 idx = 0; idx < 4; idx++){
		bool ok = true;
		i64 cur = 0;
		for (i64 m = 1; m <= n / 2; m++){
			for (i64 r = 0; r < m; r++){
				pair<i64, i64> p[4];
				p[0] = {r, m - 1};
				for (i64 l = 1; l < 4; l++){
					p[l] = {p[l - 1].second, n - 1 - p[l - 1].first};
				}
				// printmsg("p=", p, p + 4);
				for (i64 l = 0; l + 1 <= 4; l++){
					ok = ok & (l == idx || (l + 1) % 4 == idx || (a[p[l].first][p[l].second] == a[p[(l + 1) % 4].first][p[(l + 1) % 4].second]));
				}
			}
			for (i64 c = 0; c < m; c++){
				pair<i64, i64> p[4];
				p[0] = {m - 1, c};
				// printmsg("p=", p, p + 4);
				for (i64 l = 1; l < 4; l++){
					p[l] = {p[l - 1].second, n - 1 - p[l - 1].first};
				}
				for (i64 l = 0; l + 1 <= 4; l++){
					ok = ok & (l == idx || (l + 1) % 4 == idx || (a[p[l].first][p[l].second] == a[p[(l + 1) % 4].first][p[(l + 1) % 4].second]));
				}
			}
			if (!ok) break;
			++cur;
		}
		maxm = max(maxm, cur);
	}
	cout << maxm << endl;
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
