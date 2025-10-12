// #define TESTCASES
#define debug cerr

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) debug << msg; for(auto it = v.begin(); it != v.end(); it++){debug << *it << " ";} debug << endl;
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
Let f(x) := #(a[i]: a[i] ⊇ x) be the number of supermasks of x.
Then 2^f(x) = number of sets whose AND is a supermask of x (where the AND of the empty set is 2^B - 1)

Let S[x] be the set of all subsets of elements whose bitwise AND (&) is exactly x. We want S[0], and we have that
2^f(x) = |U_{y ⊇ x} S[y]| = sum(y ⊇ x)S[y] since S[y] sets are disjoint.

Let ~S[x] = S[~x], A[x] = 2^f(~x)
Actually we have that
SOS(~S)[~x] = sum(y ⊆ ~x)~S[y] = sum(y ⊆ ~x)S[~y] = sum(y ⊇ x)S[y] = 2^f(x) = A[~x]
(so sum-of-superset DP instead of sum-of-subset DP)

Therefore ~S[x] = SOS^{-1}(A)[x]
S[x] = ~S[~x] = SOS^{-1}(A)[~x]

Answer is therefore S[0] = SOS^{-1}(A)[2^B - 1]
*/

vector<i64> sosdp_MOD(const vector<i64> A, const i64 B, i64 MOD, bool inverse = false){
    assert(A.size() == (1ll << B));
    vector<i64> S = A;
    for (i64 i = 0; i < B; i++){
        // introduce possible diff at i
        for (i64 mask = (1ll << B) - 1; mask >= 0; mask--){
            if (mask & (1ll << i)){
                if (inverse){
                    S[mask] = (S[mask] + MOD - S[mask ^ (1ll << i)]) % MOD;
                } else {
                    S[mask] = (S[mask] + S[mask ^ (1ll << i)]) % MOD;
                }
            }
        }
    }
    return S;
}

vector<i64> not_arr(const vector<i64> A, const i64 B){
    vector<i64> S(1ll << B);
    for (i64 mask = 0; mask < (1ll << B); mask++){
        S[mask] = A[((1ll << B) - 1) ^ mask];
    }
    return S;
}

// SOSP(A)[x] = sum(y ⊇ x)A[x] = sum(y ⊆ ~x)A[~y] = SOS(~A)[~x] = ~SOS(~A)
// otherwise if SOSP(S) = A then
// ~SOS(~S) = A ==> SOS(~S) = ~A ==> ~S = SOS^{-1}(~A) ==> S = ~SOS^{-1}(~A)
vector<i64> supersetdp_MOD(const vector<i64> A, const i64 B, i64 MOD, bool inverse = false){
    return not_arr(sosdp_MOD(not_arr(A, B), B, MOD, inverse), B);
}

i64 bexp(i64 a, i64 p, i64 MOD){
    if (p == 0){
        return 1;
    } else {
        const i64 b = bexp(a, p / 2, MOD);
        const i64 b2 = (b * b) % MOD;
        if (p % 2 == 0) return b2;
        else return (a * b2) % MOD;
    }
}

vector<i64> bexp(i64 a, vector<i64> p, i64 MOD){
    const i64 n = p.size();
    vector<i64> ans(n);
    for (i64 i = 0; i < n; i++) ans[i] = bexp(a, p[i], MOD);
    return ans;
}

void solve(){
    const i64 B = 20;
    const i64 MOD = (i64)1e9 + 7;

    i64 n;
    cin >> n;
    vector<i64> a(n);
    vector<i64> cnt(1ll << B, 0);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        ++cnt[a[i]];
    }
    // print("cnt=", cnt);
    vector<i64> f = supersetdp_MOD(cnt, B, MOD);
    // print("f=", f);
    vector<i64> f2(1ll << B);
    vector<i64> p2(n + 1);
    for (i64 i = 0, x = 1; i <= n; i++, x = (x * 2) % MOD) p2[i] = x;
    for (i64 i = 0; i < (1ll << B); i++) f2[i] = p2[f[i]];
    // print("f2=", f2);
    vector<i64> S = supersetdp_MOD(f2, B, MOD, true);    
    // print("S=", S);
    cout << S[0] << endl;
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
