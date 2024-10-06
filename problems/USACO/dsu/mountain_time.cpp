//LINK:
//https://csacademy.com/contest/archive/task/mountain-time
//but was found under the DSU section (gold) from the USACO guide

//#define TESTCASES

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

i64 n, m;

vector<vector<i64>> a, ans;

bool valid(i64 i, i64 j){
    return (0 <= i && i < n) && (0 <= j && j < m);
}

struct DSU {
    vector<i64> p;
    vector<vector<i64>> comp;

    DSU(i64 n){
        p = vector<i64>(n);
        iota(p.begin(), p.end(), 0);
        comp = vector<vector<i64>>(n);
    }
};



void solve(){
    cin >> n >> m;
    a.assign(n, vector<i64>(m));
    p.assign(n, vector<i64>(m, -1));

    vector<> 
    for (6

    
}
 
signed main(){
	fastio;
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);
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
