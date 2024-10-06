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
 
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

const i64 INF = 2e18;

void solve(){
	i64 n;	
	cin >> n;

	i64 t[n];
	for (i64 i = 0; i < n; i++){
		cin >> t[i];
	}
	sort(t, t + n);

	vector<i64> table(2 * n + 1, -1);

	for (i64 i = 0; i < n; i++){
		i64 x = t[i];
		// complete search for the best place for x right now
		// maybe moving the block in its pos somewhere empty
		i64 min_delta = INF, final_pos_x = -1, final_pos_swapped = -1;
		for (i64 j = 1; j <= 2 * n; j++){
			i64 delta_x = abs(j - x);
			if (table[j] == -1){
				if (delta_x < min_delta){
					min_delta = delta_x;
					final_pos_x = j;
					final_pos_swapped = -1;
				}
				continue;
			} 

			i64 min_delta_y = INF;
			i64 best_pos_y = -1;
			i64 y = table[j];
			for (i64 k = 1; k <= 2 * n; k++){
				if (table[k] != -1) continue;
				i64 delta_y = abs(k - y) - abs(j - y);
				if (delta_y < min_delta_y){
					best_pos_y = k;
					min_delta_y = delta_y;
				}
			}
			if (delta_x + min_delta_y < min_delta){
				final_pos_x = j;
				final_pos_swapped = best_pos_y;
				min_delta = delta_x + min_delta_y;
			}
		}
		i64 y = table[final_pos_x];
		table[final_pos_x] = x;
		if (final_pos_swapped != -1){
			table[final_pos_swapped] = y;
		}
	}

	i64 ans = 0;
	for (i64 i = 1; i <= 2 * n; i++){
		if (table[i] != -1){
			ans += abs(table[i] - i);
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

