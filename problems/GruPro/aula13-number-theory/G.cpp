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
 
#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define print(first, last) for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
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

using cd = complex<long double>;
const i64 MOD = 998244353;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

// standard O(n^2) poly multiply
// vector<i64> multiply(vector<i64> const& a, vector<i64> const& b) {
// 	const i64 n = a.size() - 1, m = b.size() - 1;
// 	vector<i64> c(n + m + 1);
// 	for (i64 i = 0; i <= n; i++){
// 		// j + m >= i, j <= n
// 		for (i64 j = 0; j <= m; j++){
// 			c[i + j] = (c[i + j] + a[i] * b[j]) % MOD;
// 		}
// 	}
//     return c;
// }

vector<i64> multiply(vector<i64> const& a, vector<i64> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);
 
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);
 
    vector<i64> result(n);
    for (int i = 0; i < n; i++){
        result[i] = round(fa[i].real());
		result[i] %= MOD;
	}
    return result;
}

vector<i64> multiply_seq(
	vector<vector<i64>>& poly,
	i64 l, i64 r
){
	if (l == r){
		return poly[l];
	} else {
		const i64 m = l + (r - l) / 2;
		vector<i64> a = multiply_seq(poly, l, m);
		vector<i64> b = multiply_seq(poly, m + 1, r);
		return multiply(a, b);
	}
}

vector<bool> sieve(const i64 MAXN){
	vector<bool> is_prime(MAXN + 1, true);
	is_prime[0] = is_prime[1] = false;
	for (i64 i = 2; i <= MAXN; i++){
		if (!is_prime[i]) continue;
		for (i64 j = 2 * i; j <= MAXN; j += i){{
			is_prime[j] = false;
		}}
	}
	return is_prime;
}

vector<i64> fact(const i64 MAXN){
	vector<i64> f(MAXN + 1);
	f[0] = 1;
	for (i64 i = 1; i <= MAXN; i++){
		f[i] = (i * f[i - 1]) % MOD;
	}
	return f;
}

i64 bexp(i64 a, i64 p){
	if (p == 0){
		return 1;
	} else {
		const i64 b = bexp(a, p / 2);
		if (p % 2 == 0){
			return (b * b) % MOD;
		} else {
			return (a * ((b * b) % MOD)) % MOD;
		}
	}
}

i64 inv(i64 a){
	return bexp(a, MOD - 2);
}

void solve(){
	i64 n;
	cin >> n;
	const i64 MAXN = 1e6 + 10;
	vector<bool> is_prime = sieve(MAXN);
	vector<i64> f = fact(MAXN);

	vector<vector<i64>> poly;
	vector<i64> cnt(MAXN + 1, 0);
	for (i64 i = 0; i < 2 * n; i++){
		i64 x;
		cin >> x;
		++cnt[x];
	}
	for (i64 i = 0; i <= MAXN; i++){
		if (is_prime[i] && cnt[i]){
			poly.push_back({1, cnt[i]});
		}
	}
	if (poly.size() < n){
		cout << 0 << endl;
		return;
	} else {
		vector<i64> final_poly = multiply_seq(poly, 0, poly.size() - 1);
		i64 coef = final_poly[n];
		i64 ans = f[n];
		for (const i64 a: cnt){
			if (a){
				ans = (ans * inv(f[a])) % MOD;
			}
		}
		ans = (ans * coef) % MOD;
		cout << ans << endl;
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
