#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template<class T> using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

#define dbg(x) cerr << #x << " = " << x << endl;
#define int long long
#define double long double
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(),a.rend()
#define endl "\n"
const int mod = 1e9 + 7, mod2 = 998244353;
const int dx[] = { 1, 0, -1, 0 };
const int dy[] = { 0, 1, 0, -1 };     

int lcm(int a,int b){
    return a/__gcd(a,b)*b;
}

const int maxN = 2e5 + 5,maxK = 501, INF = 1e15, LOGN =21;

void solve(){
    int v,n;
    cin >> v >> n;
    // int tot = v*n;
    
    // 51/
    for(int i = 10; i <= 90; i+=10){
        cout << (v * n * i + 99) / 100 << " ";
    }
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
