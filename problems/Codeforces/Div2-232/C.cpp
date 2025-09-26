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

const i64 MOD = (i64)1e9 + 7;

vector<i64> get_primes(const i64 MAXN){
    // const i64 INF = (i64)2e18;
    vector<i64> is_prime(MAXN + 1, true);
    vector<i64> primes;
    // vector<i64> spf(MAXN + 1, INF);
    for (i64 i = 2; i <= MAXN; i++){
        if (!is_prime[i]) continue;
        // spf[i] = i;
        primes.emplace_back(i);
        for (i64 j = 2 * i; j <= MAXN; j += i){
            is_prime[j] = false;
            // spf[j] = min(spf[j], i);
        }
    }
    return primes;
}

i64 bexp(i64 a, i64 p){
    if (p == 0) return 1;
    else {
        i64 b = bexp(a, p / 2);
        i64 b2 = (b * b) % MOD;
        if (p % 2 == 0) return b2;
        else return (a * b2) % MOD;
    }
}

i64 inv(i64 x) { return bexp(x, MOD - 2); }

void solve(){
    vector<i64> primes = get_primes((i64)1e5);
    // factorization exponent is at most log_2 C <= 30 per element
    // at worst 
    const i64 MAXN = 500, MAX_EXP = 30 + 5;
    const i64 M = MAXN * MAX_EXP;
    vector<i64> fat(M + 1), ifat(M + 1);
    fat[0] = 1;
    for (i64 i = 1; i <= M; i++){
        fat[i] = (fat[i - 1] * i) % MOD;
    }
    ifat[M] = inv(fat[M]);
    for (i64 i = M - 1; i >= 0; i--){
        ifat[i] = (ifat[i + 1] * (i + 1)) % MOD;
    }

    // print("fat=", fat);
    // print("ifat=", ifat);

    auto choose = [&fat, &ifat](i64 n, i64 k){
        return (((fat[n] * ifat[k]) % MOD) * ifat[n - k]) % MOD;
    };

    i64 n;
    cin >> n;
    vector<i64> a(n);
    map<i64, i64> m_factorization;
    // O(sqrt(C) / log C * n)
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        for (i64 p: primes){
            while (a[i] % p == 0) {
                ++m_factorization[p];
                a[i] /= p;
            }
        }
        if (a[i] > 1)  { ++m_factorization[a[i]]; }  // prime > sqrt(C)
    }
    // print("m_factorization=", m_factorization);
    i64 ways = 1;
    for (auto[p, k]: m_factorization){
        // k + n - 1 <= MAXN * MAX_EXP + MAXN - 1
        // each element contributes individually with at most MAX_EXP
        ways = (ways * choose(k + n - 1, n - 1)) % MOD;
    }
    cout << ways << endl;
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