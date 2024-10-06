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

bool check(multiset<i64> &a, vector<i64> &b){
	i64 i = 0;
	bool ok = true;
	for (i64 x: a){
		ok = ok && (x <= b[i]);
		++i;
	}
	return ok;
}

void solve(){
	i64 n;
	cin >> n;
	vector<i64> b(n);
	multiset<i64> a;

	i64 x;
	for (i64 i = 0; i < n; i++){
		cin >> x;
		a.insert(x);
	}
	for (i64 i = 0; i < n; i++){
		cin >> b[i];
	}

	i64 cnt = 0;
	while (!check(a, b)){
		a.erase(a.find(*a.rbegin()));
		a.insert(1);
		++cnt;
	}
	cout << cnt << endl;
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
