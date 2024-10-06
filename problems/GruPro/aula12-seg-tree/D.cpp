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

// default BIT
struct BIT {
    vector<i64> b;
    i64 n;

    BIT(i64 n) : n(n) {
        b.assign(n + 1, 0);
    }

    void update(i64 p, i64 x){
        while (p <= n){
            b[p] += x;
            p += p & -p;
        }
    }

    i64 pref(i64 p){
        i64 ans = 0;
        while (p > 0){
            ans += b[p];
            p ^= p & -p;
        }
        return ans;
    }

    i64 range(i64 l, i64 r){
        return pref(r) - pref(l - 1);
    }
};

void solve(){
    i64 n;
    cin >> n;

    // all 1-indexed
    vector<pair<i64, i64>> a(n);
    vector<tuple<i64, i64, i64, i64>> k_queries;  // (k, l, r, idx)

    for (i64 i = 0; i < n; i++){
        cin >> a[i].first;
        a[i].second = i + 1;
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());

    i64 q;
    cin >> q;
    vector<i64> ans(q);
    BIT bit(n);
    for (i64 i = 0; i < q; i++){
        i64 k, l, r;
        cin >> l >> r >> k;
        k_queries.emplace_back(k, l, r, i);
    }
    sort(k_queries.begin(), k_queries.end());
    reverse(k_queries.begin(), k_queries.end());
    
    i64 mx = -1;
    for (auto[k, l, r, i]: k_queries){
        while (mx + 1 < n && a[mx + 1].first > k){
            bit.update(a[mx + 1].second, 1);
            ++mx;
        }
        ans[i] = bit.range(l, r);
    }
    
    for (auto x: ans){
        cout << x << endl;
    }
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
