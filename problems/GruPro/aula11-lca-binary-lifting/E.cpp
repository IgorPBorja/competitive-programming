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

struct BIT {
    vector<i64> B;
    i64 n;

    BIT(vector<i64> &a) : n(a.size()) {
        B.assign(n + 1, 0);
        for (i64 i = 0; i < n; i++){
            update_increment(i + 1, a[i]);
        }
    }

    /*
    Since B[i] = sum(j=i-2^lsb(i)+1...i)a[j]
    then each a[j] where j = b[B]...b[0] appears as a
    valid sum element in BIT of b[B]...b[k + 1]100...0 where k >= 0
    and either
    1. b[k] = 0 but not all b[k'] are 0 for k' < k
    2. or b[k] = 1 and b[k'] = 0 for all k' < k
    (so either b[k] = 0 AND k + 1 is not the lsb of j or k is the lsb of j)

    In the case 2, the mask b[B]...b[k]100...0 is simply j.

    Note that i + (i & -i) = i + 2^lsb(i) which goes to the next bit of i which is 0
    and flips it, and zeroing the suffix after (so covering the case 1, EXCEPT if this
    is just the original i (orig_i) plus 2^lsb(i)).
    However, this exception isn't really important, since it is impossible to keep adding 2^lsb(i)
    to i and get to orig_i + 2^j with j < lsb(i).
    */
    void update_increment(i64 i, i64 x){
        while (i <= n){
            B[i] += x;
            i += i & -i;
        }
    }
    
    i64 range_sum(i64 l, i64 r){
        if (l > r) {
            return 0;
        }
        return pref(r) - pref(l - 1);
    }

    i64 pref(i64 i){
        // S[i] = B[i] + S[i - 2^lsb(i)]
        // 2^lsb(i) = i & -i
        i64 ans = 0;
        while (i > 0){
            ans += B[i];
            i -= i & -i;
        }
        return ans;
    }
};

void solve(){
    i64 n, q;
    cin >> n >> q;

    // consider the array of differences 
    // d[0] = a[0], d[1] = a[1] - a[0], ..., d[n - 1] = a[n - 1] - a[n - 2]
    // then a[k] = sum(j <= k) d[j]
    // and adding u to range [a, b] means adding u to difference d[a] = A[a] - A[a - 1]
    // and subtracting u to diff d[b + 1] = A[b + 1] - A[b]

    vector<i64> a(n), d(n);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }

    d[0] = a[0];
    for (i64 i = 1; i < n; i++){
        d[i] = a[i] - a[i - 1];
    }

    BIT bit(d);
    for (i64 i = 0; i < q; i++){
        i64 mode, k, a, b, u;
        cin >> mode;
        if (mode == 1){
            cin >> a >> b >> u;
            bit.update_increment(a, u);
            bit.update_increment(b + 1, -u);
        } else {
            cin >> k;
            cout << bit.pref(k) << endl;
        }
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
