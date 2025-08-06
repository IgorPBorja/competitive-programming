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

void solve(){
    // n has O(n^{1/3}) divisors, so there are that many transitions per n
    // however, due to the method we use, we do O(sqrt(n)) iterations
    // ==> complexity is O(n*[sqrt(n) + n^(1/3) * log(n^(1/3)]))
    // since MEX of k values is k log k

    // those are independent nim games with special rules
    // so we compute grundy numbers to reduce to usual nim (with increases)
    // and take the xor of the grundy numbers
    const i64 MAXV = (i64)1e5;
    vector<i64> grundy(MAXV + 1);

    grundy[1] = 0;  // base is 1, not 0, since at x=1 we can't play (no strict divisor)
    for (i64 x = 2; x <= MAXV; x++){
        set<i64> s; 
        for (i64 y = 1; y * y <= x && y < x; y++){
            if (x % y == 0){
                s.insert(grundy[y]);
                i64 z = x/y;
                if (z != y && z < x){
                    s.insert(grundy[z]);
                }
            }
        }
        i64 mex = 0;
        for (i64 x: s){
            if (x != mex) break;
            else ++mex;
        }
        grundy[x] = mex;
    }

    i64 n;
    cin >> n;
    vector<i64> a(n);
    
    i64 xorsum = 0;
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        xorsum ^= grundy[a[i]];
    }
    if (xorsum > 0){
        cout << "Anna" << endl;
    } else {
        cout << "Bruno" << endl;
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
