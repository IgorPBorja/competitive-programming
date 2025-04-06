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
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
 
#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define print(first, last) for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
 
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
	// first position of first fill
	// min(first position of second fill, second position for first fill)

	i64 n, m;
	cin >> n >> m;
	i64 a[2][n + m + 1];
	for (i64 i = 0; i < n + m + 1; i++){
		cin >> a[0][i];
	}
	for (i64 i = 0; i < n + m + 1; i++){
		cin >> a[1][i];
	}

	i64 total_skill = 0;
	i64 cnt[2] = {0, 0};
	i64 fill[2] = {n + m - 1, n + m - 1}, second[2] = {n + m, n + m};
	i64 team[n + m + 1];
	for (i64 i = 0; i < n + m; i++){
		if (a[0][i] > a[1][i] && cnt[0] < n){
			++cnt[0];
			team[i] = 0;
			total_skill += a[0][i];
			if (cnt[0] == n){
				fill[0] = i;	
			}
		} else if (a[1][i] > a[0][i] && cnt[1] < m){
			++cnt[1];
			team[i] = 1;
			total_skill += a[1][i];
				if (cnt[1] == m){
				fill[1] = i;
			}
		} else if (cnt[0] == n){
			total_skill += a[1][i];
			team[i] = 1;
			if (a[0][i] > a[1][i]) second[0] = min(second[0], i);
		} else if (cnt[1] == m){
			total_skill += a[0][i];
			team[i] = 0;
			if (a[1][i] > a[0][i]) second[1] = min(second[1], i);
		}
	}
	i64 min_fill_type = (fill[0] < fill[1]) ? 0 : 1;
	
	// printmsg("fill=", fill, fill + 2);
	// printmsg("second=", second, second + 2);
	// printmsg("team=", team, team + n + m);

	for (i64 i = 0; i < n + m; i++){
		// removing a[i]:
		// if after first fill position: no ordering changes
		// else: first fill position becomes min(other fill position, second fill of the same type)
		// ONLY ONE team will change: the first guy of that type after than
		// OR the last will have to go into it if there is none
		if (i > min(fill[0], fill[1])){
			cout << total_skill - a[team[i]][i] + a[team[i]][n + m] << " ";
		} else {
			if (team[i] != min_fill_type){
				cout << total_skill - a[team[i]][i] + a[team[i]][n + m] << " ";
			} else {
				cout << total_skill - a[min_fill_type][i] - a[1 - min_fill_type][second[min_fill_type]] + a[min_fill_type][second[min_fill_type]] + a[1 - min_fill_type][n + m] << " ";
			}
		}
	}
	cout << total_skill << " ";
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
