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
	string base, s;
	cin >> base >> s;
	const i64 n = base.size();
	i64 target = 0;
	for (i64 i = 0; i < n; i++){
		target += (base[i] == '+') ? 1 : -1;
	}

	vector<vector<long double>> p(n + 1, vector<long double>(2 * n + 3, 0.0));
	i64 offset = n + 1; // what to sum to each in range [-n - 1, n + 1] to get [0, 2n + 2]
	p[0][0 + offset] = 1.0;
	for (i64 i = 0; i < n; i++){
		for (i64 pos = -n; pos <= n; pos++){
			if (s[i] == '?'){
				p[i + 1][pos + offset] = (long double)0.5 * (p[i][pos + offset - 1] + p[i][pos + offset + 1]);
			} else if (s[i] == '+'){
				p[i + 1][pos + offset] = p[i][pos + offset - 1];
			} else {
				p[i + 1][pos + offset] = p[i][pos + offset + 1];
			}
		}
	}
	cout << fixed << setprecision(12) << p[n][target + offset] << endl;
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
