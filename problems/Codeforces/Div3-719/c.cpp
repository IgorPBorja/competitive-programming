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

template <typename T>
ostream& operator<< (ostream& out, vector<T> x)
{
	for (auto y: x){
		out << x << " ";
	}
	return out;
}

int diagonal(vector<vector<int>>& M, int d, bool up, int& start){
	int x0, y0;
	if (up){
		x0 = 0;
		y0 = d;
	} else {
		x0 = d;
		y0 = 0;
	}
	for (int i = 0; i + d < M.size(); i++){
		M[x0 + i][y0 + i] = start;
		start++;
	}
	return start;
}

void solve(){
	int n;
	cin >> n;
	vector<vector<int>> M(n, vector<int>(n));
	if (n == 1){
		cout << 1 << endl;
	} else if (n == 2){
		cout << -1 << endl;
	} else {
		int start = 1;
		for (int d = 0; d < 2 * n - 1; d++){
			diagonal(M, (d + 1) / 2, (d % 2) == 0, start);
		}
		for (auto row: M){
			for (auto x: row){
				cout << x << " ";
			}
			cout << endl;
		}
	}
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
