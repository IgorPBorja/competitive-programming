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

	i64 base[n][n];
	for (i64 i = 0; i < n; i++){
		for (i64 j = 0; j < n; j++){
			cin >> base[i][j];
		}
	}

	i64 k;
	cin >> k;
	vector<tuple<i64, i64, i64>> roads(k);
	vector<i64> sums(k, 0);
	for (i64 i = 0; i < k; i++){
		cin >> get<0>(roads[i]) >> get<1>(roads[i]) >> get<2>(roads[i]);
		--get<0>(roads[i]); --get<1>(roads[i]);
	}

	i64 d[k + 1][n][n];
	for (i64 i = 0; i < n; i++){
		for (i64 j = 0; j < n; j++){
			d[0][i][j] = base[i][j];
		}
	}
	for (i64 idx = 0; idx < k; idx++){
		auto[a, b, w] = roads[idx];
		for (i64 i = 0; i < n; i++){
			for (i64 j = 0; j < n; j++){
				d[idx + 1][i][j] = min(d[idx][i][j], d[idx][i][a] + w + d[idx][b][j]);
				d[idx + 1][i][j] = min(d[idx][i][j], d[idx][i][b] + w + d[idx][a][j]);
				cout << "d[" << idx + 1 << "][" << i << "][" << j << "]=" << d[idx + 1][i][j] << endl;
				sums[idx] += d[idx + 1][i][j];
			}
		}
		sums[idx] /= (i64)2;  // pairs (a,b) (b,a) counted twice (with a != b). Distance (a,a) is always zero
		cout << endl;
	}
	for (i64 x: sums){
		cout << x << " ";
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
