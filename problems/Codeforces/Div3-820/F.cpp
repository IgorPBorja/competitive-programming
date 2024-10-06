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

const i64 INF = 1e18;

void solve(){
    array<vector<i64>, 9> rem;

    string s;
    cin >> s;
    const i64 n = s.size();
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++){
        a[i] = s[i] - '0';
    }
    i64 w, m;
    cin >> w >> m;

    vector<i64> pref(n + 1);
    pref[0] = 0;
    for (i64 i = 0; i < n; i++){
        pref[i + 1] = pref[i] + a[i];
    }
    for (i64 i = 0; i + w <= n; i++){
        rem[(pref[i + w] - pref[i]) % 9].emplace_back(i);
    }


    array<i64, 9> cnt;  // how many times were used
    fill(cnt.begin(), cnt.end(), 0);
    for (i64 i = 0; i < m; i++){
        i64 l, r, k;
        pair<i64, i64> solution = {INF, INF};
        cin >> l >> r >> k;
        --l; --r;  // to 0-index
        const i64 v = (pref[r + 1] - pref[l]) % 9;

        // try x for first remainder
        for (i64 x = 0; x < 9; x++){
            i64 sel_x, sel_y;
            if (rem[x].size() == 0) continue;
            ++cnt[x];
            i64 y = (k + 9 - ((v * x) % 9)) % 9;
            if (rem[y].size() > cnt[y]){
                // can spare cnt[y] + 1 (y itself)
                sel_x = rem[x][0], sel_y = rem[y][cnt[y]];
                if (pair<i64, i64>(sel_x, sel_y) < solution){
                    solution = pair<i64, i64>(sel_x, sel_y);
                }
            }
            --cnt[x];  // undo
        }
        if (solution.first == INF){
            cout << -1 << " " << -1 << endl;
        } else {
            // +1 for 1-indexing
            cout << solution.first + 1 << " " << solution.second + 1 << endl;
        }
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
