#define TESTCASES
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

const i64 MOD = (i64)1e9 + 7;

i64 bexp(i64 a, i64 p){
    if (p == 0){
        return 1;
    } else {
        i64 m = bexp(a, p / 2);
        if (p % 2 == 1){
            return (((m * m) % MOD) * a) % MOD;
        } else {
            return (m * m) % MOD;
        }
    }
}

i64 inv(i64 a){
    return bexp(a, MOD - 2);
}

struct ModInt {
    i64 x;
    ModInt() : x(0) {}
    ModInt(i64 x) : x(x % MOD) {}
    ModInt(const ModInt& other) : x(other.x) {}

    ModInt operator=(ModInt other){
        this->x = other.x;
        return *this;
    }

    ModInt operator=(i64 x){
        this->x = x % MOD;
        return *this;
    }

    ModInt operator+(i64 x){
        return (this->x + (x % MOD)) % MOD;
    }

    ModInt operator*(i64 x){
        return (this->x * (x % MOD)) % MOD;
    }

    ModInt operator+(ModInt other){
        return (this->x + other.x) % MOD;
    }

    ModInt operator*(ModInt other){
        return (this->x * other.x) % MOD;
    }
};

ostream& operator<<(ostream& os, ModInt m){
    os << m.x;
    return os;
}


void solve(){
    i64 n, m, k;
    cin >> n >> m >> k;

    i64 f[m];
    for (i64 i = 0; i < m; i++){
        i64 _;
        cin >> _ >> _;
        cin >> f[i];
    }

    ModInt p = m * inv((n * (n - 1)) / 2);
    ModInt avg = 0;
    for (i64 i = 0; i < m; i++){
        avg = avg + f[i];
    }
    avg = avg * inv(m);

    ModInt ans = avg * p * k + p * p * ((k * (k - 1)) / 2) * inv(m);
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
