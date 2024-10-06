//#define TESTCASES
 
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
 
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

const i64 MOD = 1e9 + 7;

/*
sigma(p^k) = (p^{k + 1} - 1) / (p - 1)

prod (d | p^k)d = p^(1 + ... + k) = p^(k*(k + 1) / 2)

in general if rho(x) = prod(d | x)d
then
rho(p1^x1 * ... * pk^xk) = prod_(i=0...xk)(prod(d | x / pk^xk)pk^i * d)
= prod_(i = 0...xk)[pk^(i * s(x / pk^xk)) * rho(x / pk^xk)]
= pk^(s(x / pk^xk) * xk(xk + 1) / 2) * rho(x / pk^xk) ^ (xk + 1)
*/

i64 bexp(i64 base, i64 exp){
    if (exp == 0){
        return (i64)1;
    } else{
        i64 rem = (exp % 2 == 1) ? base : 1;
        i64 mid = bexp(base, exp / 2);
        return (rem * ((mid * mid) % MOD)) % MOD;
    }
}

struct Modular{
    i64 x;
    Modular(i64 val = 0) : x(val % MOD){
        // -x = MOD-x mod MOD
        if (x < 0) x = (MOD - x) % MOD;
    }

    Modular operator+(i64 other){
        return Modular((this->x + other) % MOD);
    }

    Modular operator-(i64 other){
        return Modular((this->x + MOD - other) % MOD);
    }

    Modular operator*(i64 other){
        return Modular((this->x * other) % MOD);
    }

    Modular operator/(i64 other){
        return Modular((this->x * bexp(other, MOD - 2)) % MOD);
    }

    Modular operator+(Modular other){
        return Modular((this->x + other.x) % MOD);
    }

    Modular operator-(Modular other){
        return Modular((this->x + MOD - other.x) % MOD);
    }

    Modular operator*(Modular other){
        return Modular((this->x * other.x) % MOD);
    }

    Modular operator/(Modular other){
        return Modular((this->x * bexp(other.x, MOD - 2)) % MOD);
    }
} typedef Modular;

Modular exp(Modular base, i64 exp){
    return Modular(bexp(base.x, exp));
}

Modular exp(Modular base, Modular exp){
    return Modular(bexp(base.x, exp.x));
}

Modular inv(Modular base){
    return Modular(bexp(base.x, MOD - 2));
}

void solve(){
    int n;
    cin >> n;

    Modular s = Modular(1), sigma = Modular(1), rho = Modular(1);
    i64 s_mod_phi = 1;
    Modular pk;
    i64 xk;
    for (int i = 0; i < n; i++){
        cin >> pk.x >> xk;
        sigma = sigma * (exp(pk, xk + 1) - 1) * inv(pk - 1);
        
        i64 pk_exp = (
            ((xk * (xk + 1)) / 2) % (MOD - 1) * s_mod_phi
        ) % (MOD - 1); // Fermat little theorem
        Modular pk_factor = exp(pk, pk_exp);
        rho = exp(rho, xk + 1) * pk_factor;

        s = s * (xk + 1);
        s_mod_phi = (s_mod_phi * (xk + 1)) % (MOD - 1);
    }
    cout << s.x << " " << sigma.x << " " << rho.x << endl;
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
