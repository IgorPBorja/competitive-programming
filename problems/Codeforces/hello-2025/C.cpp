#define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
 
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define print(first, last) for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define printgraph(msg, G) cout << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

constexpr i64 B = 30;

// O(log max(l, r)) since lcp happens at most once
void f(i64 l, i64 r, i64 pref = 0){
    vector<i64> bl, br;
    const i64 _l = l, _r = r;
    while (l > 0){
        bl.emplace_back(l % 2);
        l >>= 1;
    }
    reverse(bl.begin(), bl.end());
    while (r > 0){
        br.emplace_back(r % 2);
        r >>= 1;
    }
    reverse(br.begin(), br.end());
    // do lcp
    // lcp is at least one unless there is a power of two in the middle
    if (bl.size() != br.size()){
        // find power of two just below r
        r = _r; l = _l;
        i64 p2 = 1;
        while ((p2 * 2) <= r){
            p2 <<= 1;
        }
        // we might have that l == p2 - 1 in which case we use r?
        if (l != p2 - 1){
            cout << pref + p2 << " " << pref + p2 - 1 << " " << pref + l << endl;
        } else {
            cout << pref + r << " " << pref + p2 << " " << pref + p2 - 1 << endl;
        }
        return;
    }
    i64 lcp = 0;
    i64 extra = 0;
    while (lcp < bl.size() && bl[lcp] == br[lcp]){
        extra += bl[lcp] * (1ll << (bl.size() - 1 - lcp));
        ++lcp;
    }
    if (lcp == 0){
        // 0 and 2^k - 1 mod some large power 2^j w/ j > k
        i64 k = bl.size();
        cout << pref + (1ll << k) - 1 << " " << pref + (1ll << (k - 1)) << " " << pref << endl;
        return;
    }
    i64 mod = (1ll << (bl.size() - lcp));
    return f(_l % mod, _r % mod, pref + extra);
}

void solve(){
    i64 l, r;
    cin >> l >> r;
    f(l, r);
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
