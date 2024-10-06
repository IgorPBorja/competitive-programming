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

void fix(i64& p1, i64& p2, i64& p3, i64& p4, i64& cnt){
	i64 r1 = (p1 + p3) % 2, r2 = (p2 + p3) % 2, r4 = p4 % 2;

	if (r1 == 0 && r2 == 0 && r4 == 0) return;

	if (r4 == 1){
		--p4;
	}
	if(r1 == 1 && r2 == 1){
		if (p3 > 0){
			--p3;
		} else {
			--p1;
			--p2;
		}
	} else if (r1 == 1 && r2 == 0){
		if (p1 > 0){
			--p1;
		} else {
			--p3;
			--p2;
		}
	} else if (r1 == 0 && r2 == 1){
		if (p2 > 0){
			--p2;
		} else {
			--p3;
			--p1;
		}
	} 
	++cnt;
}

void solve(){
	i64 p1, p2, p3, p4;
	cin >> p1 >> p2 >> p3 >> p4;


	i64 cnt = 0;
	if (
		((p1 + p3) % 2 == 0)
		&& ((p2 + p3) % 2 == 0)
		&& p4 % 2 == 0
	){
		++cnt; // initial victory
	}
	fix(p1, p2, p3, p4, cnt);
	cnt += p4 / 2;
	p4 = 0;

	// fix
	fix(p1, p2, p3, p4, cnt);
	cnt += p3 / 2;
	p3 -= 2 * (p3 / 2);
	// try to match the remainder
	if (p3 == 1){
		// since was fixed, must have at least 1 p1 and 1 p2
		--p3;
		--p1;
		--p2;
		++cnt;
	}
	fix(p1, p2, p3, p4, cnt);

	i64 d = min(p1, p2);
	p1 -= d;
	p2 -= d;
	cnt += d;

	fix(p1, p2, p3, p4, cnt);
	if (p1 > 0){
		cnt += p1 / 2;
		p1 = p1 % 2;
	}
	else if (p2 > 0){
		cnt += p2 / 2;
		p2 = p2 % 2;
	}
	fix(p1, p2, p3, p4, cnt);
	cout << cnt - 1 << endl;
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
