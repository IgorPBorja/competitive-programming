#define TESTCASES
 
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

const i64 INF = 2e18;

void solve(){
    i64 n;
    cin >> n;
    i64 a[n];
    set<i64> s;
    i64 m = -1;
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        m = max(m, a[i]);
        s.insert(a[i]);
    }
    // check if this is not a divisor array
    for (i64 i = 0; i < n; i++){
        if (m % a[i] != 0){
            cout << n << endl;
            return;
        }
    }
    vector<i64> divM;
    for (i64 i = 1; i * i <= m; i++){
        if (m % i == 0){
            divM.emplace_back(i);
            if (m / i != i){
                divM.emplace_back(m / i);
            }
        }
    }
    sort(divM.begin(), divM.end());
    const i64 d = divM.size();
    vector<i64> cnt(d);
    for (i64 i = 0; i < n; i++){
        ++cnt[lower_bound(divM.begin(), divM.end(), a[i]) - divM.begin()];
    }
    map<i64, i64> sol;
    for (i64 i = 0; i < n; i++){
        map<i64, i64> tmp;
        for (auto[j, c]: sol){
           tmp[lcm(a[i], j)] = c + 1;
        }
        sol[a[i]] = max(sol[a[i]], (i64)1);
        for (auto[j, c]: tmp){
            sol[j] = max(sol[j], c);
        }
    }
    i64 ans = 0;
    for (i64 i = 0; i < d; i++){
        if (sol[divM[i]] != 0 && cnt[i] == 0){
            ans = max(ans, sol[divM[i]]);
        }
    }
    cout << ans << endl;
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
