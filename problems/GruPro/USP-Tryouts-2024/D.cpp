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

using ld = long double;

bool inside_sphere(
    ld px, ld py, ld pz,
    ld cx, ld cy, ld cz,
    ld r
){
    return 
        (px - cx) * (px - cx)
        + (py - cy) * (py - cy)
        + (pz - cz) * (pz - cz)
        < r * r
    ;
}

bool check(
    ld x, ld y, ld z,
    ld tx, ld ty, ld tz,
    ld r, ld R // candidate radius
){
    /*
    we must have:
    R <= cx <= x - R
    R <= cy <= y - R
    R <= cz <= z - R

    sphere of radius r+R must not contain box [R, x-R] x [R, y-R], [R, z-R]
    which, by convexity, is equivalent to one of the box points being outside
    */
    bool ok = false;
    for (ld bx: {R, x - R}){
        for (ld by: {R, y - R}){
            for (ld bz: {R, z - R}){
                ok |= !inside_sphere(bx, by, bz, tx, ty, tz, r + R);
            }
        }
    }
    return ok;
}

void solve(){
    ld x, y, z;
    ld tx, ty, tz, r;
    cin >> x >> y >> z;
    cin >> tx >> ty >> tz >> r;
    ld ans = 0.0f;
    
    ld epsilon = (ld)(1e-9);
    // we must have R <= x - R, etc, ohterwise check might not work
    ld lo = 0.0, hi = min(x, min(y, z)) / (ld)(2.0f);
    while (hi - lo > epsilon){
        const ld R = (lo + hi) / (ld)(2.0f);
        if (check(x, y, z, tx, ty, tz, r, R)){
            ans = R;
            lo = R;
        } else {
            hi = R;
        }
    }
    cout << fixed << setprecision(20) << ans << endl;
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
