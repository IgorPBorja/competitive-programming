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
#define printmsg(msg, first, last) debug << msg; for(auto it = first; it != last; it++){debug << *it << " ";} debug << endl;
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

// factor a single number in O(sqrt(x))
// return list of pairs (p, p^vp(x))
vector<pair<i64, i64>> factor(i64 x){
    vector<pair<i64, i64>> f;
    for (i64 p = 2; p * p <= x; p++){
        if (x % p == 0){
            i64 pk = 1;
            while (x % p == 0){
                pk *= p;
                x /= p;
            }
            f.emplace_back(p, pk);
        }
    }
    if (x > 1) {  // what remains is a prime
        f.emplace_back(x, x);
    }
    return f;
}

/*
Let pi(n) be the Pisano Period (https://en.wikipedia.org/wiki/Pisano_period)

Theorem 1: pi(mn) = lcm(pi(m), pi(n)) if gcd(m, n) = 1
Theorem 2: pi(p^k) | p^{k - 1} * pi(p)
Theorem 3: if p != 2,5 then:
    * If p = +-1 mod 10 then pi(p) | p - 1
    * If p = +-3 mod 10 then pi(p) | 2(p + 1)
And pi(2) = 3, pi(5) = 20

Therefore, let 
q(p^k) := {
    3 2^{k-1} if p = 2
    20 * 5^{k - 1} = 4 * 5^k if p = 5
    (p-1)p^{k - 1} if p = +- 1 mod 10
    2*(p + 1)p^{k - 1} if p = +- 3 mod 10
}
q(p1^a1 * ... * pk^ak) := lcm(q(p1^a1), ..., q(pk^ak))

Then q(x) is a multiple of pi(x) for all x, and therefore q(M)
can act as a period length for M:

F(a^b) mod M = F(a^b mod q(M)) mod M
*/

i64 period(const vector<pair<i64, i64>> factorization){
    i64 q = 1;
    for (auto[p, pk]: factorization){
        cout << "p=" << p << " pk=" << pk << endl;
        i64 period_pk;
        if (p == 2){
            period_pk = (pk / 2) * 3;
        } else if (p == 5){
            period_pk = (pk / 5) * 20;
        } else if (p % 10 == 1 || p % 10 == 9){
            period_pk = (pk / p) * (p - 1);
        } else {  // +- 3 mod 10
            period_pk = (pk / p) * 2 * (p + 1);
        }
        q = (q * period_pk) / __gcd(q, period_pk);  // lcm
    }
    cout << "period=" << q << endl;
    return q;
}

i64 bexp_period(i64 a, i64 p, i64 period){
    // if b = 2^i1 + ... + 2^ik
    // then we keep squaring 
    // and multiply the base number when we get to some active bit
    i64 res = 1;
    i64 power = a;
    for (i64 i = 0; i < 32; i++, power = (power * power) % (i64)period){
        if (p & (1ll << i)){
            res = (res * power) % period;          
        }
    }
    return res;
}

vector<vector<i64>> matmul(
    const vector<vector<i64>>& A, const vector<vector<i64>>& B,
    i64 mod
){
    vector<vector<i64>> C(2, vector<i64>(2));
    for (i64 i = 0; i < 2; i++){
        for (i64 j = 0; j < 2; j++){
            C[i][j] = 0;
            for (i64 k = 0; k < 2; k++){
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
            }
        }
    }
    return C;
}

vector<vector<i64>> mat_bexp(vector<vector<i64>> A, i64 p, i64 mod){
    vector<vector<i64>> Id(2, vector<i64>(2, 0));
    Id[0][0] = Id[1][1] = 1;
    vector<vector<i64>> B = A;
    vector<vector<i64>> C = Id;
    for (i64 i = 0; i < 32; i++, B = matmul(B, B, mod)){
        if (p & (1ll << i)){
            C = matmul(C, B, mod);
        }
    }
    return C;
}

void solve(){
    i64 a, b, M;
    cin >> a >> b >> M;

    // F^k = ((f[k + 1], f[k]), (f[k], f[k - 1]))
    vector<vector<i64>> F(2, vector<i64>(2, 0));
    F[0][0] = F[0][1] = F[1][0] = 1;
    i64 period_multiple = period(factor(M));
    i64 exp = bexp_period(a, b, period_multiple);
    vector<vector<i64>> Fpow = mat_bexp(F, exp, M);

    cout << Fpow[0][1] << endl;
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
