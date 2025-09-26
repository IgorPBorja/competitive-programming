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
I am guessing we do similar to D1:

l <= 2^n <= r and then go backwards to the left and forwards to the right

2^n - 1 2^n ... 2^n - d, 2^n + (d - 1)

l <= 2^n - d && 2^n + (d - 1) <= r
==> d <= min(r + 1 - 2^n, 2^n - l)

Then we solve the remaining segments

Should be O(n log n)?
*/

constexpr i64 B = 31;

bool shares_power_of_two(i64 l, i64 r){
    return __builtin_clzll((u64)l) == __builtin_clzll((u64)r);
}

// base offset is the first l
i64 f(vector<i64>& a, i64 pos_offset, i64 l, i64 r, i64 val_offset = 0){
    // cerr << "at l=" << l << " r=" << r << " pos_offset=" << pos_offset << " val_offset=" << val_offset << endl;
    if (l > r) return 0;
    if (l == r) {
        a[l - pos_offset] = val_offset + l;
        return l;
    }

    i64 val = 0;
    while (shares_power_of_two(l, r) && l > 0) {
		// cerr << "at l=" << l << " r=" << r << endl;
        // has no powers of two. Find first unmatching digit
        // and solve for that!
        // Remaining prefix will stay the same
        i64 largest_prefix = 0;
        for (i64 i = B; i >= 0; i--){
            if ((l & (1ll << i)) == (r & (1ll << i))){
                largest_prefix += (l & (1ll << i));
            } else break;
        }
        // guaranteed > 0
        val += largest_prefix * (r - l + 1);
        pos_offset -= largest_prefix;
		val_offset += largest_prefix;
        l -= largest_prefix;
        r -= largest_prefix;
    }
    i64 n = 0;
    while ((1ll << n) < l) ++n;
    // now 2^n >= l and is minimum
    while ((1ll << (n + 1)) <= r) ++n;
    // cerr << "for l=" << l << " r=" << r << " n=" << n << endl;
    // now 2^n <= r and is maximum

    // 2^n - 1 - d >= l
    // 2^n + d <= r
    i64 d = min(r - (1ll << n), (1ll << n) - l - 1);
    // cerr << "for l=" << l << " r=" << r << " d=" << d << endl;
    for (i64 j = 0; j <= d; j++){
        i64 x1 = (1ll << n) - 1 - j;
        i64 x2 = (1ll << n) + j;
        a[x1 - pos_offset] = x2 + val_offset;
        a[x2 - pos_offset] = x1 + val_offset;
        val += 2 * (x1 | x2);
    }
    // cerr << "base pairing=" << val << endl;
    val += f(a, pos_offset, l, (1ll << n) - 1 - (d + 1), val_offset);
    val += f(a, pos_offset, (1ll << n) + (d + 1), r, val_offset);
    return val;
}

void solve(){
    i64 l, r;
    cin >> l >> r;
    vector<i64> a(r - l + 1);
    i64 ans = f(a, l, l, r);
    cout << ans << endl;
    for (i64 i = 0; i <= r - l; i++){
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
