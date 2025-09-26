#define TESTCASES
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

/*
OR is sum minus and

x | y = x + y - x&y

sum is an invariant. Thus, minimize matches!
(greedily)

MINIMIZE matches
*/

// returns max value
// will make at most log r calls since p2 decreases everytime
i64 fill_optimal(vector<i64>& a, i64 r){
    i64 p2 = 0;
    while ((1ll << (p2 + 1)) <= r + 1) ++p2;
    // we now 2^p2 - 1 <= r and it is the last

    if ((1ll << p2) - 1 == r){
        // just reverse
        i64 val = 0;
        for (i64 i = 0; i <= r; i++) {
            val += (i | (r - i));
            a[i] = r - i;
        }
        return val;
    }

    // match last of first block with first of last, and so on
    i64 r1 = (1ll << p2), r2 = (1ll << p2) - 1;
    i64 val = 0;
    for (; r1 <= r; r1++, r2--){
        a[r1] = r2;
        a[r2] = r1;
        val += (r1 | r2) + (r2 | r1);
    }
    // now solve for 0..r2
    val += fill_optimal(a, r2);
    return val;
}

void solve(){
    i64 _, r;
    cin >> _ >> r;
    vector<i64> a(r + 1);
    i64 ans = fill_optimal(a, r);
    cout << ans << endl;

    for (i64 i = 0; i <= r; i++){
        cout << a[i] << " ";
    }
    cout << endl;
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
