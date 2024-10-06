// https://codeforces.com/problemset/gymProblem/104375/H

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

i64 bexp(i64 a, i64 p, i64 mod){
    if (p == 0){
        return 1;
    } else {
        const i64 b = bexp(a, p / 2, mod);
        if (p % 2 == 0){
            return (b * b) % mod;
        } else {
            return (a * ((b * b) % mod)) % mod;
        }
    }
}

const i64 MOD = (i64)1e9 + 7;
const i64 p = 31;
const i64 m1 = (i64)1e9 + 7, m2 = (i64)1e9 + 9;
const i64 MAX_SIZE = 2e5 + 10;
const i64 q1 = bexp(p, m1 - 2, m1), q2 = bexp(p, m2 - 2, m2);

array<i64, MAX_SIZE> p1_pow, p2_pow;
array<i64, MAX_SIZE> inv1_pow, inv2_pow;

i64 isqrt(i64 n){
    i64 l = 1, r = n, ans = 1;
    while (l <= r){
        i64 m = l + (r - l) / 2;
        if (m * m <= n){
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return ans;
}

vector<pair<i64, i64>> rolling_hash(string s){
    i64 cur1 = 0, cur2 = 0;
    vector<pair<i64, i64>> v;
    v.emplace_back(0, 0);
    for (i64 i = 0; i < s.size(); i++){
        cur1 = (cur1 + (s[i] - 'a' + 1) * p1_pow[i]) % m1;
        cur2 = (cur2 + (s[i] - 'a' + 1) * p2_pow[i]) % m2;
        v.emplace_back(cur1, cur2);
    }
    return v;
}

pair<i64, i64> hash_str(string s){
    auto v = rolling_hash(s);
    return v.back();
}

// inclusive indices
inline pair<i64, i64> substr(const vector<pair<i64, i64>>& h, i64 i, i64 j){
    return make_pair(
        ((h[j + 1].first - h[i].first + m1) % m1) * inv1_pow[i] % m1,
        ((h[j + 1].second - h[i].second + m2) % m2) * inv2_pow[i] % m2
    );
}

void solve(){
    p1_pow[0] = p2_pow[0] = inv1_pow[0] = inv2_pow[0] = 1;
    for (i64 i = 1; i <= MAX_SIZE; i++){
        p1_pow[i] = (p1_pow[i - 1] * p) % m1;
        p2_pow[i] = (p2_pow[i - 1] * p) % m2;
        inv1_pow[i] = (inv1_pow[i - 1] * q1) % m1;
        inv2_pow[i] = (inv2_pow[i - 1] * q2) % m2;
    }
    
    i64 n;
    cin >> n;
    unordered_map<i64, i64> cnt[MAX_SIZE + 1];

    string s;
    i64 total = 0;
    set<pair<i64, i64>> _large;
    for (i64 i = 0; i < n; i++){
        cin >> s;
        pair<i64, i64> x = hash_str(s);
        ++cnt[s.size()][x.first * m2 + x.second];
        total += s.size();
    }
    const i64 t = isqrt(total);
    for (i64 i = t + 1; i <= MAX_SIZE; i++){
        for (auto[x, c]: cnt[i]){
            _large.insert(make_pair(i, x));
        }
    }
    vector<pair<i64, i64>> large;
    large.reserve(_large.size());
    for (auto& p: _large) large.emplace_back(p);

    cin >> s;
    vector<pair<i64, i64>> h = rolling_hash(s);
    i64 dp[s.size() + 1];
    dp[0] = 1;
    // TODO handle duplicates in word list
    for (i64 i = 0; i < s.size(); i++){
        // try small combinations
        dp[i + 1] = 0;
        for (i64 dx = 1; dx <= min(t, i + 1); dx++){
            // size dx -> from i - dx + 1 to i
            // we need this hash, which 
            const pair<i64, i64> x = substr(h, i - dx + 1, i);
            if (cnt[dx][x.first * m2 + x.second] != 0){
                dp[i + 1] = (dp[i + 1] + dp[i - dx + 1]) % MOD;
            }
        }
        // try large now
        for (auto[sz, x]: _large){
            if (sz > i + 1) break;
            auto[y1, y2] = substr(h, i - sz + 1, i);
            i64 y = y1 * m2 + y2;
            if (y == x){
                dp[i + 1] = (dp[i + 1] + dp[i - sz + 1]) % MOD;
            }
        }
    }
    // printmsg("small_cnt=", small_cnt.begin(), small_cnt.end());
    // printmsg("large=", large.begin(), large.end());
    // printmsg("large_sz=", large_sz.begin(), large_sz.end());
    // printmsg("h=", h.begin(), h.end());
    // printmsg("dp=", dp, dp + s.size() + 1);
    cout << dp[s.size()] << endl;
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
