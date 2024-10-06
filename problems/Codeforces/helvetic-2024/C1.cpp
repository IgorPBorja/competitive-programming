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
 
#define print(vec) for(auto x: vec){cerr << x << "|";} cerr << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

void solve(){
	i64 n, t;
	cin >> n >> t;

	vector<i64> p(n, -1), pr(n, -1);
	i64 u, v;
	for (i64 i = 0; i < n - 1; i++){
		cin >> u >> v;
		--u; --v;
		p[u] = v;
		pr[v] = u;
	}

	// find leaves
	i64 l, r;
	for (i64 i = 0; i < n; i++){
		if (pr[i] == -1) l = i;
		if (p[i] == -1) r = i;
	}
	// print(p);
	// print(pr);

	// get idx
	i64 k;
	cin >> k;
	--k; // to 0-index
	i64 ik = 0, cur = l;
	for (; cur != k; ik++, cur = p[cur]);
	if ((ik % 2) == 0 && (n - 1 - ik) % 2 == 0){
		// first player always loses
		cout << "Hermione" << endl;
	} else {
		cout << "Ron" << endl;
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
