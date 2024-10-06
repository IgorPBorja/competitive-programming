// #define TESTCASES
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

const i64 MOD = 1ll << 15;
const i64 INF = 1e18;

void solve(){
    i64 q, n, t;
    cin >> q >> n >> t;

    pair<i64, i64> c[n];
    pair<i64, i64> item[q];
    i64 ans[n];

    for (i64 i = 0; i < q; i++){
        cin >> item[i].first >> item[i].second;
    }
    sort(item, item + q);

    for (i64 i = 0; i < n; i++){
        cin >> c[i].first;
        c[i].second = i;
    }
    sort(c, c + n);

    // printmsg("c=", c, c + n);
    // printmsg("itens=", item, item + q);

    i64 l = 0;
    min_pq<i64> waiting;
    max_pq<i64> on;
    i64 s = 0;
    for (i64 i = 0; i < n; i++){
        i64 added = 0;
        for (; l < q && item[l].first <= c[i].first; l++){
            waiting.emplace(item[l].second);
            ++added;
        }
        // remove the bad ones as much as possible
        for (i64 j = 0; j < added && !on.empty(); j++){
            i64 max_t = on.top();
            s -= max_t;
            on.pop();
            waiting.emplace(max_t);
        }
        // re-add all over again
        while (!waiting.empty() && s + waiting.top() <= t){
            i64 min_t = waiting.top();
            s += min_t;
            waiting.pop();
            on.emplace(min_t);
        }
        ans[c[i].second] = on.size();
    }

    for (i64 i = 0; i < n; i++){
        cout << ans[i] << endl;
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
