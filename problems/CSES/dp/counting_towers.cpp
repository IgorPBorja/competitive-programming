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
 
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

const i64 MOD = (i64)1e9 + 7;

class Modular {
public:
    i64 x;
    Modular() {}
    Modular(i64 x){
        this->x = x;
    }
    Modular (const Modular &m){
        this->x = m.x;
    }
    Modular operator=(Modular other){
        this->x = other.x;
        return *this;
    }
    Modular pow(i64 p){
        if (p == 0){
            return *this;
        } else {
            Modular half = this->pow(p / 2);
            if (p % 2 == 0){
                return half * half;
            } else {
                return half * half * Modular(this->x);
            }
        }
    }
    Modular operator+(Modular other){
        return Modular((this->x + other.x) % MOD);
    }
    void operator+=(Modular other){
        this->x = (this->x + other.x) % MOD;
    }
    Modular operator-(Modular other){
        return Modular((this->x + MOD - other.x) % MOD);
    }
    void operator-=(Modular other){
        this->x = (this->x + MOD - other.x) % MOD;
    }
    Modular operator*(Modular other){
        return Modular((this->x * other.x) % MOD);
    }
    void operator*=(Modular other){
        this->x = (this->x * other.x) % MOD;
    }
    Modular operator/(Modular other){
        return (*this) * other.pow(MOD - 2);
    }
    void operator/=(Modular other){
        Modular m = (*this) * other.pow(MOD - 2);
        this->x = m.x;
    }
};

const i64 MAXN = 1e6;
Modular dp3exp[MAXN + 1];
Modular dpsum[MAXN + 1];
Modular dp[MAXN + 1];

void solve(){
        i64 n;
        cin >> n;
        cout << dp[n].x << endl;
}
 
signed main(){
        dp[0] = Modular(1);
        dpsum[0] = Modular(1);
        dp3exp[0] = Modular(1);
        for (i64 i = 1; i <= MAXN; i++){
            dp[i] = dp3exp[i - 1] + dpsum[i - 1];
            dp3exp[i] = Modular(3) * dp3exp[i - 1] + dp[i];
            dpsum[i] = dpsum[i - 1] + dp[i];
        }
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
