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
 
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

void solve(){
	i64 n;
	cin >> n;

	string names[n];
	map<string, i64> idx;
	i64 ages[n];
	for (i64 i = 0; i < n; i++){
		cin >> names[i];
		idx[names[i]] = i;
	}
	for (i64 i = 0; i < n; i++){
		string s;
		cin >> s;
		ages[idx[s]] = i + 1;
	}


	// do suffix argmin
	i64 suffix_min[n];
	string suffix_argmin[n];
	suffix_argmin[n - 1] = names[n - 1], suffix_min[n - 1] = ages[n - 1];
	for (i64 i = n - 2; i >= 0; i--){
		suffix_min[i] = min(ages[i], suffix_min[i + 1]);
		suffix_argmin[i] = (ages[i] < suffix_min[i + 1]) ? names[i] : suffix_argmin[i + 1];
	}
	for (i64 i = 0; i < n; i++){
		cout << suffix_argmin[i];
		if (i < n - 1) { cout << " "; }
		else { cout << endl; }
	}
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
