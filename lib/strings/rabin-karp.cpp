#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

vector<i64> rollingHash(const vector<int>& v, i64 p, i64 m){
    const i64 n = v.size();
    vector<i64> prefH(n);
    vector<i64> p_pow(n);
    // prefH = hash(v[0...i]) = sum(j<=i) v[j] * p^j mod m
    p_pow[0] = 1;
    prefH[0] = v[0] % m;
    for (i64 i = 1; i < n; i++){
        p_pow[i] = (p_pow[i - 1] * p) % m;
        prefH[i] = (v[i] * p_pow[i] + prefH[i - 1]) % m;
    }
    return prefH;
}

// lowercase
vector<i64> rollingHash(const string& s){
    vector<int> s_repr(s.size());
    for (i64 i = 0; i < s.size(); i++){
        s_repr[i] = s[i] - 'a';
    }
    return rollingHash(s_repr, 31, (i64)1e9 + 7);
}

i64 bexp(const i64 a, const i64 p, const i64 mod){
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

vector<i64> prime_powers(const i64 n, const i64 p = 31, const i64 m = (i64)1e9 + 7){
    vector<i64> p_pow(2 * n + 1);
    p_pow[n] = 1;
    p_pow[n - 1] = bexp(p, m - 2, m);   // fermat little theorem
    for (i64 i = 1; i <= n; i++){
        p_pow[n + i] = (p_pow[n + i - 1] * p) % m;
    }
    for (i64 i = 2; i <= n; i++){
        p_pow[n - i] = (p_pow[n - i + 1] * p_pow[n - 1]) % m;
    }
    return p_pow;
}

vector<i64> rabinKarpMatch(const string& s, const string& t){
    vector<i64> prefix_s = rollingHash(s), prefix_t = rollingHash(t);

    const i64 mod = (i64)1e9 + 7, p = 31;
    const i64 HS = prefix_s.back();  // complete hash of s
    // precompute prime powers mod M
    const vector<i64> p_pow = prime_powers(t.size(), p, mod);

    vector<i64> matches;  // starting points of matches

    const i64 offset = t.size();
    for (i64 i = 0; i + s.size() <= t.size(); i++){
        // hash of t[i...i + |s| - 1] == (hash(t[0...i + |s| - 1]) - hash(t[0...i - 1])) * p^-i
        const i64 h = ((prefix_t[i + s.size() - 1] - (i > 0 ? prefix_t[i - 1] : 0) + mod) * p_pow[offset - i]) % mod;
        if (h != HS){
            continue;
        }
        // compare
        bool ok = true;
        for (i64 j = 0; (j < s.size()) && ok; j++){
            ok = ok && (s[j] == t[i + j]);
        }
        if (ok) matches.emplace_back(i);
    }
    return matches;
}
