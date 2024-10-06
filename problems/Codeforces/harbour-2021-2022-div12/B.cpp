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

bool solve(string& s, string& t, i64 i, i64 j, bool only_left=false){
	if (j == t.size()){
		return true; // base case
		// has to be checked first since landing outside s (with i) is fine if j ended
	} else if (i < 0 || i >= s.size()){
		return false; // ended in bad pos
	} else if (s[i] != t[j]){
		return false;
	}
	if (only_left){
		return solve(s, t, i - 1, j + 1, true);
	} else {
		bool left_solve = solve(s, t, i - 1, j + 1, true);
		bool right_solve = solve(s, t, i + 1, j + 1, false);
		return left_solve || right_solve;
	}
}

void solve(){
	string s, t;
	cin >> s >> t;
	const i64 n = s.size();

	bool ok = false;
	for (i64 i = 0; i < n; i++){
		// choosing starting position
		if (s[i] == t[0]) ok = ok || solve(s, t, i, 0);
	}
	if (ok){
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
}
 
signed main(){
	fastio;
// #ifdef DEBUG
// 	freopen("/tmp/in", "r", stdin);
// #endif
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
