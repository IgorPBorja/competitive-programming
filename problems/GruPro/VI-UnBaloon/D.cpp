// #define TESTCASES
#define debug cerr

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define printmsg(msg, first, last) debug << msg; for(auto it = first; it != last; it++){debug << *it << " ";} debug << endl;
#define printgraph(msg, G) debug << msg << endl; \
	for (u64 u = 0; u < G.size(); u++) { \
		debug << "G[" << u << "]="; \
		for (u64 v: G[u]) { \
			debug << v << " "; \
		} \
		debug << endl; \
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

const long double PI = acos(-1);

void solve(){
    i64 rl, hl, rc, hc;
    cin >> rl >> hl >> rc >> hc;

    // pi * rc^2 * hc / 3 + 2 pi * rc^3 / 3 <= pi * rl^2 * hl
    // <==> rc^2 * hc / 3 * 2/3 rc^3 <= rl^2 * hl
    // <==> rc^2 * hc + 2 rc^3 <= 3 * rl^2 * hl

    if (3 * rl * rl * hl > rc * rc * hc + 2 * rc * rc * rc){
        cout << "Injusto" << endl;
    } else {
        cout << "Justo" << endl;
    }
    // long double cilinder = PI * rc * rc * hc;
    // long double cone = (PI * rl * rl * hl) / ((long double)3.0);
    // // half of 4/3 pi r^3
    // long double semisphere = ((long double)2.0 * PI * rl * rl * rl) / ((long double)3.0);
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
