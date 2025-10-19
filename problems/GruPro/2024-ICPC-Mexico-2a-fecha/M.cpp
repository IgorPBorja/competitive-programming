// #define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
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

using ld = long double;

const ld PI = acos((ld)(-1));

ld f(ld theta, ld d, ld l){
    // let d = 2 * r be the diameter of the base
    ld VOL = PI * d * d * l * sin(theta) -
            (ld)2.0 * PI * d * l * l * sin(theta) * cos(theta)
            + (ld)4.0 / (ld)3.0 * PI * l * l * l * sin(theta) * cos(theta) * cos(theta);
    return VOL;
}

// argmax with golden section search
ld gss(ld a, ld b, ld (*f)(ld, ld, ld), ld diameter, ld side){
    ld r = (sqrt((ld)5) - (ld)1) / (ld)2, eps = 1e-9;
    ld x1 = b - r * (b - a), x2 = a + r*(b-a);
    ld f1 = f(x1, diameter, side), f2 = f(x2, diameter, side);
    while (b - a > eps){
        if (f1 > f2){
            b = x2; x2 = x1; f2 = f1;
            x1 = b - r * (b - a); f1 = f(x1, diameter, side);
        } else {
            a = x1; x1 = x2; f1 = f2;
            x2 = a + r * (b - a); f2 = f(x2, diameter, side);
        }
    }
    return a;
}

void solve(){
    i64 n;
    cin >> n;
    for (i64 i = 0; i < n; i++){
        ld l, r;
        cin >> l >> r;
        ld diam = r * (ld)2.0f;
        ld theta_max = gss(PI / ((ld)2.0), PI, f, diam, l);
        cout << fixed << setprecision(12) << theta_max << endl;
    }
}
 
signed main(){
	fastio;
	int t = 1;
#ifdef TESTCASES
	cin >> t;
#endif
	while (t--){
		solve();
	}
}
