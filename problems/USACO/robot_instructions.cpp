// NOTE: Link: https://usaco.org/index.php?page=viewproblem2&cpid=1207

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
 
#define printv(msg, vec) cout << msg; for(auto x: vec){cout << x << "|";} cout << endl
#define printm(msg, map) cout << msg; cout << "{";for(auto[x, y]: map){cout << x << ":" << y << ",";} cout << "}" << endl
 
// template <typename T, typename U>
// ostream& operator<< (ostream& out, pair<T, U> x)
// {
// 	out << "(" << x.first << " " << x.second << ")";
// 	return out;
// }

template <typename T>
pair<T, T> operator+(pair<T, T> p, pair<T, T> q){
    return {p.first + q.first, p.second + q.second};
}
template <typename T>
pair<T, T> operator-(pair<T, T> p, pair<T, T> q){
    return {p.first - q.first, p.second - q.second};
}

/*
lemma: sum of vector is monotonic w.r.t lexicographic order (if x <= y, x + z <= y + z)
proof:
    let x[1] == y[1], ..., x[i] == y[i] and x[i + 1] <= y[i + 1]
    Then (x+z)[1] == (y+z)[1], ..., (x+z)[i] == (y+z)[i]

    and (x+z)[i + 1] <= (y+z)[i + 1]
    which means x+z <= y+z

So now we can use two pointers algorithm: we sort left tuples in normal order, right tuples in reverse mode.
    if l[i] can't use r[j] anymore because l[i] is too large, neither will l[i + delta] for all delta, so we can move the ptr
*/

void solve(){
    i64 n;
    i64 xg, yg;

    cin >> n;
    cin >> xg >> yg;

    i64 x[n], y[n];
    for (i64 i = 0; i < n; i++){
        cin >> x[i] >> y[i];
    }

    i64 l = (n + 1) / 2, r = n / 2;
    vector<pair<pair<i64, i64>, i64>> prefixes;
    vector<pair<pair<i64, i64>, i64>> suffixes;

    // O(N * 2^{N // 2}
    for (i64 mask = 0; mask < (1ll << l); mask++){
        i64 x0 = 0, y0 = 0;
        for (i64 i = 0; i < l; i++){
            if (mask & (1ll << i)){
                x0 += x[i];
                y0 += y[i];
            }
        }
        prefixes.emplace_back(make_pair(x0, y0), __builtin_popcount(mask));
    }

    for (i64 mask = 0; mask < (1ll << r); mask++){
        i64 x0 = 0, y0 = 0;
        for (i64 i = 0; i < r; i++){
            if (mask & (1ll << i)){
                x0 += x[l + i];
                y0 += y[l + i];
            }
        }
        suffixes.emplace_back(make_pair(x0, y0), __builtin_popcount(mask));
    }

    // O(N * 2^{N / 2}
    sort(prefixes.begin(), prefixes.end());
    sort(suffixes.begin(), suffixes.end());
    reverse(suffixes.begin(), suffixes.end());

    vector<i64> total(n + 1, 0);

    const pair<i64, i64> pg = make_pair(xg, yg);
    i64 j = 0;
    pair<i64, i64> last_p = make_pair(-1e18, -1e18);
    vector<i64> valid_right_offsets;  // memmorization

    // O(N * 2^{N / 2}) because the j ptr only moves 2^{N / 2} steps
    for (auto[p, i]: prefixes){
        if (p > last_p){
            // prompts change in offsets
            // can discard now the ones that will be too high
            valid_right_offsets.clear();
            valid_right_offsets.assign(r + 1, 0);
            for (; j < suffixes.size() && p + suffixes[j].first > pg; j++);
            for (; j < suffixes.size() && p + suffixes[j].first == pg; j++){
                ++valid_right_offsets[suffixes[j].second];
            }
            last_p = p;
        }
        for (i64 k = 0; k <= min((i64)valid_right_offsets.size(), r); k++){
                total[i + k] += valid_right_offsets[k];
        }
    }
    for (i64 i = 1; i <= n; i++){
        cout << total[i] << endl;
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
