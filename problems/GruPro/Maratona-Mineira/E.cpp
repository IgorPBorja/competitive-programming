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

const i64 MAXR = 2e5;
vector<i64> houses[MAXR + 1];

void solve(){
	i64 n;
	cin >> n;

	i64 r, c;
	for (i64 i = 0; i < n; i++){
		cin >> r >> c;
		houses[r].emplace_back(c);
	}

	i64 total = 0;
	for (i64 r = 0; r <= MAXR; r++){
		if (houses[r].size() == 0){
			continue;
		}
		sort(houses[r].begin(), houses[r].end());
		i64 sz = houses[r].size();
		i64 med_1 = (houses[r][(sz - 1) / 2] + houses[r][sz / 2]) / 2;
		i64 med_2 = (houses[r][(sz - 1) / 2] + houses[r][sz / 2] + 1) / 2;

		i64 min_d = 2e18, d = 0;
		for (i64 x: houses[r]){
			d += max(x - med_1, med_1 - x);
		}
		min_d = min(min_d, d);

		d = 0;
		for (i64 x: houses[r]){
			d += max(x - med_2, med_2 - x);
		}
		min_d = min(min_d, d);
		total += min_d;
	}
	cout << total << endl;
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
