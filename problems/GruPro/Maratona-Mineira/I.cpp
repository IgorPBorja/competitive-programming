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

const i64 MAXV = 2e5;
i64 mult_seq[MAXV + 1];
i64 cnt[MAXV + 1];

void solve(){
	i64 n, x;
	cin >> n;

	for (i64 i = 0; i < n; i++){
		cin >> x;
		++cnt[x];
	}

	mult_seq[1] = cnt[1];
	for (i64 x = 2; x <= MAXV; x++){
		mult_seq[x] = mult_seq[1] + cnt[x];
		for (i64 d = 2; d * d <= x; d++){
			if (x % d == 0){
				mult_seq[x] = max(mult_seq[x], mult_seq[d] + cnt[x]);
				mult_seq[x] = max(mult_seq[x], mult_seq[x / d] + cnt[x]);
			}
		}
	}

	cout << *max_element(begin(mult_seq), end(mult_seq)) << endl;
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
