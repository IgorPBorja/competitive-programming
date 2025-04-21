#define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
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

void solve(){
    i64 n, s;
    cin >> n >> s;
    i64 a[n];
    vector<i64> ones;

    i64 t = 0;
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        if (a[i]) ones.emplace_back(i);
        t += a[i];
    }

    if (t < s){
        cout << -1 << endl;
        return;
    }

    const i64 k = ones.size();
    // i64 left_cost[k], right_cost[k];
    // i64 cur_l = 0;
    // for (i64 i = 0; i < k; i++){
    //     left_cost[i] = ones[i] + 1 - cur_l;  // from cur_l to ones[i]+1
    //     cur_l = ones[i] + 1;
    // }

    // i64 cur_r = n-1;
    // for (i64 i = k - 1; i >= 0; i--){
    //     // from cur_r to ones[i]-1
    //     right_cost[i] = cur_r - (ones[i]-1);
    //     cur_r = ones[i] - 1;
    // }

    // i64 prefL[k+1], sufR[k+1];
    // prefL[0] = 0;
    // for (i64 i = 0; i < k; i++) prefL[i+1] = prefL[i] + left_cost[i];
    // sufR[k] = 0;
    // for (i64 i = k; i >= 0; i--) sufR[i] = sufR[i + 1] + right_cost[i];

    i64 ops = (i64)2e9;;
    i64 d = t-s;
    for (i64 l = 0; l <= d; l++){
        // take out ones[0]...ones[l-1]
        // and ones[k-1]...ones[k-(d-l)]
        // which costs ones[l-1] + 1 + (n-1-ones[k-(d-l)] + 1)
        i64 c1 = (l > 0) ? (ones[l - 1] + 1) : 0;
        i64 c2 = (l < d) ? (n - ones[k - (d-l)]) : 0;
        ops = min(ops, c1 + c2);
    }
    cout << ops << endl;
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
