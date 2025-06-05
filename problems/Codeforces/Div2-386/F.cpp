// #define TESTCASES
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

set<pair<i64, i64>> top_w;
set<pair<i64, i64>, greater<pair<i64, i64>>> bottom;
i64 best = 0;
i64 cur_a = 0, cur_t = 0;
i64 n, k, w;
i64 t[(i64)2e5 + 1];
i64 a[(i64)2e5 + 1];

inline bool can_expand_half(i64 r){
    return (i64)top_w.size() < w && cur_t + (t[r] + 1) / 2 <= k;
}

inline bool can_replace_to_half(i64 r){
    if (top_w.empty()) return false;
    auto [tmin, imin] = *top_w.begin();
    // -(tmin+1)/2 + tmin + (t[r]+1)/2
    return (tmin/2 + (t[r] + 1) / 2 < t[r]) && (cur_t + tmin/2 + (t[r] + 1)/2 <= k);
}

inline bool can_expand_full(i64 r){
    return cur_t + t[r] <= k;
}

void expand_half(i64 r){
    top_w.emplace(t[r], r);
    cur_t += (t[r] + 1) / 2;
    cur_a += a[r];
    best = max(best, cur_a);
}

void move_to_full(){
    auto [tmin, imin] = *top_w.begin();
    top_w.erase(top_w.begin());
    bottom.emplace(tmin, imin);
    // from ceil(tmax/2) to tmax
    cur_t += tmin / 2;
}

void move_to_half(){
    auto [tmax, imax] = *bottom.begin();
    bottom.erase(bottom.begin());
    top_w.emplace(tmax, imax);
    // from tmax to ceil(tmax/2)
    cur_t -= tmax / 2;
}

void expand_to_full(i64 r){
    bottom.emplace(t[r], r);
    cur_t += t[r];
    cur_a += a[r];
    best = max(best, cur_a);
}

void solve(){
	cin >> n >> w >> k;

	for (i64 i = 0; i < n; i++) cin >> a[i];
	for (i64 i = 0; i < n; i++) cin >> t[i];

	i64 r = -1;

	for (i64 l = 0; l < n; l++){
		if (l > 0 && r >= l - 1){  // range existed before
			// remove a[l - 1]
			if (top_w.find(make_pair(t[l - 1], l - 1)) != top_w.end()){
				top_w.erase(make_pair(t[l - 1], l - 1));
				cur_t -= (t[l - 1] + 1) / 2;
                // can get someone (greatest one) onto the half set and improve things
                if (!bottom.empty()){
                    move_to_half();
                }
			} else {
				cur_t -= t[l - 1];
                bottom.erase(make_pair(t[l - 1], l - 1));
			}
			cur_a -= a[l - 1];
		}
		r = max(r, l - 1);
		while (r + 1 < n){
            if (can_expand_half(r + 1)){
                expand_half(r + 1);
                ++r;
                continue;
            }
			else if (top_w.size() == 0){
				// can't replace, too large to expand into special
				break;
			}

			// now necesarily top_w.size() > 0
			// try replacing special
			// can replace and replacing is better than simple expansion
            if (can_replace_to_half(r + 1)){
                move_to_full();
                expand_half(r + 1);
                ++r;
                continue;
            }
			// try to just expand
			else if (can_expand_full(r + 1)){
                expand_to_full(r + 1);
				++r;
				continue;
			}
			break;
		}
	}
	cout << best << endl;
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
