// #define TESTCASES
#define DEBUG
 
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

const i64 M = 1e4;

void solve(){
    i64 n;
    cin >> n;
    
    vector<i64> x, y;
    vector<i64> cnt(M + 1, 0);
    
    i64 d;
    for (i64 i = 0; i < n; i++){
        cin >> d;
        ++cnt[d];
    }
    
    // add repeated
    for (i64 i = 1; i <= M; i++){
        if (cnt[i] == 2){
            x.emplace_back(i);
            y.emplace_back(i);
            cnt[i] = 0;
        }
    }
    
    for (i64 i = 1; i <= M; i++){ // O(M * N^2)
        if (cnt[i] == 0) continue;
        // try to add to x and see if closure breaks
        i64 ok_x = true;
        for (i64 d: x){ // O(N^2)
            i64 e = (d * i) / __gcd(d, i);
			cerr << "e=" << e << endl;
            bool can_close = (find(x.begin(), x.end(), e) != x.end()) || (cnt[e] > 0);
            ok_x = ok_x && can_close;
        }
        if (ok_x){
            // add to x and close
            vector<i64> dx;
            for (i64 d: x){
                cnt[(d * i) / __gcd(d, i)] = 0;
                dx.emplace_back((d * i) / __gcd(d, i));
            }
            for (i64 d: dx){
                x.emplace_back(d);
            }
            x.emplace_back(i);
        } else {
            // add to y
            // don't need to calculate closure of y though
            y.emplace_back(i);
        }
    }
    
    //print(x);
    //print(y);
    
    // calculate x and y from max divisors
    i64 vx = *max_element(x.begin(), x.end());
    i64 vy = *max_element(y.begin(), y.end());
    cout << vx << " " << vy << endl;
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

