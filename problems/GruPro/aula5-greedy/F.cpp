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

const i64 MOD = 998244353;



void solve(){
    // start (greedily) with one piece of tape per broken segment
    // merge the n -k closer segments
    // distance from i to i + 1 is a[i + 1] - a[i] - 1 = #{a[i] + 1, ..., a[i + 1] - 1}
    
    i64 n, _, k;
    cin >> n >> _ >> k;
    
    i64 d[n - 1];
    i64 cur, prox;
    cin >> cur;
    for (i64 i = 0; i < n - 1; i++){
        cin >> prox;
        d[i] = prox - cur - 1;
        cur = prox;
    }
    sort(d, d + n - 1);
    
    i64 total = n;
    for (i64 i = 0; i < n - k; i++){
        total += d[i];
    }
    cout << total << endl;
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
