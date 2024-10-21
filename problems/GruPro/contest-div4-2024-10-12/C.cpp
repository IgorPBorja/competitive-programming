#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define endl '\n'
using namespace std;

void solve(){
    // find spf of x, p
    // put u = (x / p) - 1 and v = 1
    // then a = pu = x - p and b = pv = p with gcd(a,b) = p and lcm(a,b) = x - p
    // if x is prime, then 1 and p - 1 is a solution
    int x;
    cin >> x;
    for (int p = 2; p * p <= x; p++){
        if (x % p == 0){
            cout << x - p << " " << p << endl;
            return;
        }
    }
    cout << x - 1 << " " << 1 << endl;
}

int main(){
    fastio;
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}