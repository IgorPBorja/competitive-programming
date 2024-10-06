#define TESTCASES
 
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

i64 clocksub(i64 x, i64 y, i64 n){
	if (x < y){
		return n + (x - y) - 1;
	} else {
		return x - y - 1;
	}
}

void solve(){
	i64 n, x, y;
	// note: internal vertices inside x-polygon do not matter
	// ONLY BORDERS
	cin >> n >> x >> y;

	vector<i64> marked(x);
	for (i64 i = 0; i < x; i++){
		cin >> marked[i];
		--marked[i];
	}
	sort(marked.begin(), marked.end());

	i64 tri = x - 2;   // internal triangles
	for (i64 i = 0; i < x; i++){
		// is start of external triangle?
		if (marked[(i + 1) % x] == (marked[i] + 2) % n){
			++tri;
		}
	}
	// sort intervals
	vector<i64> odd_intervals, even_intervals;
	for (i64 i = 0; i < x; i++){
		i64 k = clocksub(marked[(i + 1) % x], marked[i], n);
		if (k % 2 == 0){
			even_intervals.emplace_back(k);
		} else {
			odd_intervals.emplace_back(k);
		}
	}
	sort(odd_intervals.begin(), odd_intervals.end());
	sort(even_intervals.begin(), even_intervals.end());
	for (i64 k: odd_intervals){
		if (k == 1) continue;
		// put min(k / 2, y) pts
		tri += min(2 * y, 2 * (k / 2));
		if ((k / 2) <= y){
			// look for closing triangle
			++tri;
		}
		y -= min(y, k / 2);
	}
	for (i64 k: even_intervals){
		if (k == 0) continue;
		tri += min(2 * y, 2 * (k / 2));
		y -= min(y, k / 2);
	}
	cout << tri << endl;
}
 
signed main(){
	fastio;
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
