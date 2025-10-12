#define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) cerr << msg; for(auto it = v.begin(); it != v.end(); it++){cerr << *it << " ";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; \
	for (i64 u = 0; u < G.size(); u++) { \
		cerr << "G[" << u << "]="; \
		for (i64 v: G[u]) { \
			cerr << v << " "; \
		} \
		cerr << endl; \
	}
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}
template <typename T>
ostream& operator<< (ostream& out, vector<T> v)
{
	for (const auto& x: v){
		out << x << " ";
	}
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

/*
H2 >= H1 * ((B-1)^n / B^n) = H1 * (1 - 1/B)^n
<==> 

should work with double, maybe?
*/

using ld = long double;

ld bexp(ld a, i64 p){
    if (p == 0){
        return 1.0;
    } else {
        const ld b = bexp(a, p / 2);
        if (p % 2 == 0){
            return b * b;
        } else {
            return b * b * a;
        }
    }
}

void solve(){
    i64 h1, h2, b;
    cin >> h1 >> h2 >> b;
    ld x = (ld)h2 / (ld)h1;
    ld a = ((ld)1.0 - (ld)1.0/(ld)b);

    // at the worst H2 = 1, H1 = 10^12, B = 2 * 10^5
    // then (1 - 1/(2 * 10^5))^ans <= 10^(-12)
    // ans <= 10^7 is enough, gets to E-22 and precision error is minimal
    // cerr << "a=" << a << " target=" << x << endl;
    
    i64 l = 0, r = (i64)10'000'000, ans = (i64)10'000'000;
    while (l <= r){
        const i64 mid = l + (r - l) / 2;
        const ld y = bexp(a, mid);
        if (y <= x){
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << endl;
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
