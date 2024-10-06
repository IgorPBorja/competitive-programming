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
#define i32 int32_t
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

/*
we want lower bound on the seg

// will do iterative
*/

const i64 B = 20;
const i64 MAXN = 1ll << B;

const i32 INF = 2e9;
i32 a[MAXN];
// for each power 2^i (0 <= i <= B)
// we will store max(j..j + 2^i-1) for all j offset by 2^i
// so for i=0 we save the array, ..., for i=B we save the global max
// and we will do the same for the reverse array

// table[i][j] = max(j*2^i..j*2^i + 2^i - 1) for j = 0...2^(B-i)-1
// = max(max(j*2*2^{i - 1}...j*2*2^{i-1} + 2^{i-1} - 1), max((2j + 1) * 2^{i - 1}, (2j + 1) * 2^{i - 1} + 2^{i - 1} - 1))
vector<i32> sparse[B + 1];

void build(i32 h[], vector<i32> table[]){
    table[0].resize(1ll << B);
    for (i64 i = 0; i < MAXN; i++){
        table[0][i] = h[i];
    }
    for (i64 i = 1; i <= B; i++){
        table[i].resize(1ll << (B - i));
        for (i64 j = 0; j < (1ll << (B - i)); j++){
            table[i][j] = max(
                table[i - 1][2 * j],
                table[i - 1][2 * j + 1]
            );
        }
    }
}

i64 right_lb(i32 x, i64 l, vector<i32> table[]){
    while (true){
        i64 last = (l == 0) ? B : __builtin_ctz(l);
        // start searching on first level, but delay as much as possible
        i64 ans = -1;
        // "bsearch" for the last i s.t [l, l+2^i) is a valid interval and with range max < x
        for (i64 j = 0; j <= last; j++){
            if (table[j][l >> j] < x){
                ans = j;
            } else {
                break;
            }
        }
        if (ans == -1) break;
        l += (1ll << ans);
    }
    return l;
}

struct frac {
    i64 a, b;

    frac(i64 a, i64 b) : a(a), b(b) {}
};

frac max(frac f1, frac f2){
    if (f1.a * f2.b >= f2.a * f1.b){
        return f1;
    } else {
        return f2;
    }
}

ostream& operator<<(ostream& os, frac f){
    i64 d = __gcd(f.a, f.b);
    if (f.b / d == 1){
        os << f.a / d;
    } else {
        os << f.a / d << "/" << f.b / d;
    }
    return os;
}


void solve(){
    i64 n;
    cin >> n;
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }
    for (i64 i = n; i < MAXN; i++){
        a[i] = INF;
    }
    build(a, sparse);
    frac ans = frac(0, 1);
    for (i64 i = 0; i < n; i++){
        i64 j = right_lb(a[i], i + 1, sparse);
        if (a[j] == INF) continue;
        // we can go i...j-1 and partial (a[i] - a[j - 1]) / (a[j] - a[j - 1])
        ans = max(
            ans,
            frac((j - 1 - i) * (a[j] - a[j - 1]) + a[i] - a[j - 1], a[j] - a[j - 1])
        );
    }

    reverse(a, a + n);
    build(a, sparse);
    reverse(a, a + n);
    for (i64 i = 0; i < n; i++){
        // 0 ... i-1 i i+1 ... n-1
        // becomes 
        // 0 ... n-i-2 n-i-1 n-i ... n-1
        // so we do n-1-IDX
        i64 j = n - 1 - right_lb(a[i], n - i, sparse);
        if (j < 0 || a[j] == INF) continue;
        // we can go j+1...i and partial (a[i] - a[j + 1]) / (a[j] - a[j + 1])
        ans = max(
            ans,
            frac((i - j - 1) * (a[j] - a[j + 1]) + a[i] - a[j + 1], a[j] - a[j + 1])
        );
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

