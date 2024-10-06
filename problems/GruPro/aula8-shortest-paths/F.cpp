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

const i64 INF = 1e16;

void solve(){
	string s, t;
	cin >> s >> t;
	if (s.size() != t.size()){
		cout << -1 << endl;
		return;
	}

	vector<vector<i64>> adj(26, vector<i64>(26, INF));
	i64 dist[26][26];
	for (i64 i = 0; i < 26; i++) for (i64 j = 0; j < 26; j++) dist[i][j] = ((i == j) ? 0 : INF);
	i64 n;
	cin >> n;

	for (i64 i = 0; i < n; i++){
		i64 w;
		string c1, c2;
		cin >> c1 >> c2;
		cin >> w;
		dist[c1[0] - 'a'][c2[0] - 'a'] = min(dist[c1[0] - 'a'][c2[0] - 'a'], w);
	}
	for (i64 k = 0; k < 26; k++){
		// can use k
		for (i64 i = 0; i < 26; i++){
			for (i64 j = 0; j < 26; j++){
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	i64 make_equal_cost[26][26];
	char bridge[26][26];
	for (i64 i = 0; i < 26; i++){
		for (i64 j = 0; j < 26; j++){
			make_equal_cost[i][j] = INF;
			for (i64 k = 0; k < 26; k++){
				if (dist[i][k] + dist[j][k] < make_equal_cost[i][j]){
					bridge[i][j] = k + 'a';
					make_equal_cost[i][j] = dist[i][k] + dist[j][k];
				}
			}
		}
	}

	string ans(s);
	i64 sum = 0;
	for (size_t i = 0; i < s.size(); i++){
		if (make_equal_cost[s[i] - 'a'][t[i] - 'a'] == INF){
			cout << -1 << endl;
			return;
		}
		ans[i] = bridge[s[i] - 'a'][t[i] - 'a'];
		sum += make_equal_cost[s[i] - 'a'][t[i] - 'a'];
	}
	cout << sum << endl;
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
