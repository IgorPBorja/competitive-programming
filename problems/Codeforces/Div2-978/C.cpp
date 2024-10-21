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

const i64 INF = 2e9;

void solve(){
    i64 n;
    cin >> n;
    vector<vector<i64>> a(n, vector<i64>(2));
    i64 top[n], bot[n], full[n];
    for (i64 i = 0; i < 2; i++){
        string s;
        cin >> s;
        for (i64 j = 0; j < n; j++){
            a[j][i] = (s[j] == 'A') ? 1 : 0;
        }
    }

    auto gettop = [&a](i64 i){
        return (a[i][0] + a[i - 1][0] + a[i - 1][1] >= 2) ? 1 : 0;
    };
    auto getbot = [&a](i64 i){
        return (a[i][1] + a[i - 1][0] + a[i - 1][1] >= 2) ? 1 : 0;
    };
    auto getfull_top = [&a](i64 i){
        return (a[i][0] + a[i][1] + a[i - 1][0] >= 2) ? 1 : 0;
    };
    auto getfull_bot = [&a](i64 i){
        return (a[i][0] + a[i][1] + a[i - 1][1] >= 2) ? 1 : 0;
    };
    auto get_ltop = [&a](i64 i){
        return (a[i][0] + a[i - 1][0] + a[i - 2][0] >= 2) ? 1 : 0;
    };
    auto get_lbot = [&a](i64 i){
        return (a[i][1] + a[i - 1][1] + a[i - 2][1] >= 2) ? 1 : 0;
    };

    top[0] = -INF; bot[0] = -INF; full[0] = full[1] = -INF;
    top[1] = gettop(1), bot[1] = getbot(1);
    for (i64 i = 2; i < n; i++){
        top[i] = (full[i - 2] != -INF) ? gettop(i) + full[i - 2] : -INF;
        bot[i] = (full[i - 2] != -INF) ? getbot(i) + full[i - 2] : -INF;
        if (i >= 3){
            top[i] = max(
                top[i], 
                (top[i - 3] != -INF) ? get_ltop(i) + get_lbot(i - 1) + top[i - 3] : -INF
            );
            bot[i] = max(
                bot[i], 
                (bot[i - 3] != -INF) ? get_lbot(i) + get_ltop(i - 1) + bot[i - 3] : -INF
            );
        }
        full[i] = max(
            (bot[i - 1] != -INF) ? getfull_top(i) + bot[i - 1] : -INF,
            (top[i - 1] != -INF) ? getfull_bot(i) + top[i - 1] : -INF
        );
        if (i == 2){
            full[i] = max(full[i], (i64)(get_ltop(i) + get_lbot(i)));
        } else {
            full[i] = max(
                full[i],
                (full[i - 3] != -INF) ? get_ltop(i) + get_lbot(i) + full[i - 3] : -INF
            );
        }
    }
    cout << full[n - 1] << endl;
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
