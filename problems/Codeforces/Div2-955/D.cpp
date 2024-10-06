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

i64 subarray_sum(vector<vector<i64>>& a, i64 x0, i64 y0, i64 x1, i64 y1){
    i64 ans = 0;
    for (i64 i = x0; i < x1; i++){
        for (i64 j = y0; j < y1; j++){
            ans += a[i][j];
        }
    }
    return ans;
}

void solve(){
    i64 n, m, k;
    cin >> n >> m >> k;

    vector<vector<i64>> a(n, vector<i64>(m));
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }

    vector<vector<i64>> w(n, vector<i64>(m));
    for (i64 i = 0; i < n; i++){
        string row;
        cin >> row;
        for (i64 j = 0; j < m; j++){
            w[i][j] = (row[j] == '1') ? 1 : -1;
        }
    }

    vector<vector<i64>> k_squares(n - k + 1, vector<i64>(m - k + 1));
    vector<vector<i64>> pref(n, vector<i64>(m));
    pref[0][0] = w[0][0];
    for (i64 j = 1; j < m; j++){
        pref[0][j] = pref[0][j - 1] + w[0][j];
    }
    for (i64 i = 1; i < n; i++){
        pref[i][0] = pref[i - 1][0] + w[i][0];
    }
    for (i64 i = 1; i < n; i++){
        for (i64 j = 1; j < m; j++){
            pref[i][j] = pref[i][j - 1] + pref[i - 1][j] - pref[i - 1][j - 1] + w[i][j];
        }
    }

    k_squares[0][0] = pref[k - 1][k - 1];
    for (i64 j = 1; j + k <= m; j++){
        k_squares[0][j] = pref[k - 1][j + k - 1] - pref[k - 1][j - 1];
    }
    for (i64 i = 1; i + k <= n; i++){
        k_squares[i][0] = pref[i + k - 1][k - 1] - pref[i - 1][k - 1];
    }
    for (i64 i = 1; i + k <= n; i++){
        for (i64 j = 1; j + k <= m; j++){
            k_squares[i][j] = pref[i + k - 1][j + k - 1] - pref[i - 1][j + k - 1] - pref[i + k - 1][j - 1] + pref[i - 1][j - 1];
        }
    }

    i64 g;
    bool ok = false;
    for (i64 i = 0; i + k <= n; i++){
        for (i64 j = 0; j + k <= m; j++){
            if (!ok && k_squares[i][j] != 0){
                g = k_squares[i][j];
                ok = true;
            } else if (k_squares[i][j] != 0){
                g = __gcd(g, max(k_squares[i][j], -k_squares[i][j]));
            }
        }
    }

    i64 target = 0;
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            target += a[i][j] * w[i][j];
        }
    }
    target = max(target, -target);

    if (!ok) {
        cout << ((target == 0) ? "YES" : "NO") << endl;
    } else {
        cout << ((target % g == 0) ? "YES" : "NO") << endl;
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
