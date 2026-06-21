#define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) cerr << msg; for(auto it = v.begin(); it != v.end(); it++){cerr << *it << " ";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; \
	for (i64 u = 0; u < G.size(); u++) { \
		cerr << "G[" << u << "]="; \
		for (i64 v: G[u]) { \
			cerr << v << " "; \
		} \
		cerr << endl; \
	}
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}
template <typename T>
ostream& operator<< (ostream& out, vector<T> v)
{
	for (const auto& x: v){
		out << x << " ";
	}
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

i64 mex_expand_from_position(const vector<i64>& a, i64 p){
    // assert(a[p] == 0);
    const i64 n = a.size();
    i64 d = min(p, n - 1 - p);
    vector<i64> visited(n, false);
    visited[0] = true;
    i64 mex = 1;
    for (i64 i = 1; i <= d; i++){
        if (a[p - i] != a[p + i]) break;
        else {
            visited[a[p - i]] = true;
            while (mex < n && visited[mex]) ++mex;
        }
    }
    return mex;
}

void solve(){
    i64 n;
    cin >> n;
    vector<i64> a(2 * n);
    vector<i64> zero_pos;
    for (i64 i = 0; i < 2 * n; i++) {
        cin >> a[i];
        if (a[i] == 0) zero_pos.emplace_back(i);
    }
    sort(zero_pos.begin(), zero_pos.end());
    // cerr << "zero pos=" << zero_pos[0] << "," << zero_pos[1] << endl;

    i64 max_mex = max(mex_expand_from_position(a, zero_pos[0]), mex_expand_from_position(a, zero_pos[1]));
    // cerr << "OK" << endl;

    // try both zeros
    bool inside_is_palindrome = true;
    vector<i64> vis(2 * n, false);
    vis[0] = true;
    i64 cur_mex = 1;
    for (i64 i = zero_pos[0] + 1; i < zero_pos[1]; i++){
        // l+1..i..r-1 ==> d = i-l ==> j = r-d
        i64 flipped_i = zero_pos[1] - (i - zero_pos[0]);
        inside_is_palindrome &= (a[i] == a[flipped_i]);
        if (inside_is_palindrome){
            vis[a[i]] = true;
            while (cur_mex < n && vis[cur_mex]) ++cur_mex;
        } else break;
    }
    // cerr << "inside is palindrome=" << inside_is_palindrome << endl;
    // try to expand even more
    if (inside_is_palindrome) {  // is valid to use both zeros
        i64 l = zero_pos[0] - 1, r = zero_pos[1] + 1;
        while (l >= 0 && r < 2 * n && a[l] == a[r]){
            vis[a[l]] = true;
            while (cur_mex < n && vis[cur_mex]) ++cur_mex;
            --l; ++r;
        }
        // cerr << "l=" << l << " r=" << r << endl;

        // update
        max_mex = max(max_mex, cur_mex);
    }

    cout << max_mex << endl;
}
 
signed main(){
	fastio;
	int t = 1;
#ifdef TESTCASES
	cin >> t;
#endif
	while (t--){
		solve();
	}
}
