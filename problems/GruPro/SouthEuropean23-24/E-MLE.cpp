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

// max seg
const i64 MAXN = (i64)1e6 + 10;
const i64 B = 20;
i64 sparse[B][MAXN];
i64 rev_sparse[B][MAXN];

void build(i64 a[], i64 n){
    for (i64 i = 0; i < n; i++){
        sparse[0][i] = a[i];
        rev_sparse[0][i] = a[i];
    }
    for (i64 i = 1; i < B; i++){
        for (i64 j = 0; j < n; j++){
            sparse[i][j] = max(
                sparse[i - 1][j],
                sparse[i - 1][min(j + (i64)(1ll << (i - 1)), n - 1)]
            );
            rev_sparse[i][j] = max(
                rev_sparse[i - 1][j],
                rev_sparse[i - 1][max(j - (i64)(1ll << (i - 1)), (i64)0)]
            );
        }
    }
}

i64 right_lb(i64 l, i64 a[], i64 n){
    i64 x = a[l];
    ++l; // otherwise it will always be >= x
    for (i64 i = B - 1; i >= 0; i--){
        if (l >= n) break;
        if (sparse[i][l] < x){
            l += 1ll << i;
        }
    }
    return l;
}

i64 left_lb(i64 l, i64 a[]){
    i64 x = a[l];
    --l; // otherwise it will always be >= x
    for (i64 i = B - 1; i >= 0; i--){
        if (l < 0) break;
        if (rev_sparse[i][l] < x){
            l -= 1ll << i;
        }
    }
    return l;
}

struct frac {
    i64 a, b;
    
    frac(i64 a, i64 b) : a(a), b(b) {};
};

ostream& operator<<(ostream& os, frac f){
    i64 d = __gcd(f.a, f.b);
    if (f.b / d == 1){
        os << f.a / d;
    } else {
        os << f.a / d << "/" << f.b / d;
    }
    return os;
}

frac max(frac f1, frac f2){
    if (f1.a * f2.b >= f2.a * f1.b){
        return f1;
    } else {
        return f2;
    }
}

void solve(){
    i64 n;
    cin >> n;
    i64 a[n];
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }
    build(a, n);

    frac ans = frac(0, 1);
    // left to right
    for (i64 i = 0; i < n; i++){
        i64 idx = right_lb(i, a, n);
        if (idx >= n) continue;
        // i..idx-1 + (a[i] - a[idx - 1]) / (a[idx] - a[idx - 1])
        // there is no +1 because those are lines, so we do |a-b| instead of |a-b| + 1
        frac partial = frac((idx - i - 1) * (a[idx] - a[idx - 1]) + a[i] - a[idx - 1], a[idx] - a[idx - 1]);
        // cout << "for i=" << i << " left-to-right ans=" << partial << endl;
        ans = max(ans, partial);
    }
    // right to left
    for (i64 i = 0; i < n; i++){
        i64 idx = left_lb(i, a);
        if (idx < 0) continue;
        // idx+1..i and (a[i] - a[idx + 1]) / (a[idx] - a[idx + 1])
        frac partial = frac((i - idx - 1) * (a[idx] - a[idx + 1]) + a[i] - a[idx + 1], a[idx] - a[idx + 1]);
        // cout << "for i=" << i << " right-to-left ans=" << partial << endl;
        ans = max(ans, partial);
    }
    cout << ans << endl;
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
