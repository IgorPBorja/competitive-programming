// #define TESTCASES
#define debug cerr

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define printmsg(msg, first, last) debug << msg; for(auto it = first; it != last; it++){debug << *it << " ";} debug << endl;
#define printgraph(msg, G) debug << msg << endl; \
	for (u64 u = 0; u < G.size(); u++) { \
		debug << "G[" << u << "]="; \
		for (u64 v: G[u]) { \
			debug << v << " "; \
		} \
		debug << endl; \
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

i64 inversions(vector<i64>& a, i64 l = -1, i64 r = -1){
    if (l == -1 && r == -1){
        const i64 n = a.size();
        l = 0, r = n - 1;
    }
    if (l == r) return 0;
    const i64 m = l + (r - l) / 2;
    i64 total = inversions(a, l, m) + inversions(a, m + 1, r);
    // now it is sorted
    vector<i64> left, right;
    for (i64 i = l; i <= m; i++) left.emplace_back(a[i]);
    for (i64 i = m + 1; i <= r; i++) right.emplace_back(a[i]);

    i64 idx = l;
    i64 pl = 0, pr = 0;
    while (pl < left.size() || pr < right.size()){
        // we only count the inversion pairs from the perspective of the smaller
        // element on the right
        // 1 3 5 | 2 4
        // if right[pr] < left[pl] then it is smaller than [left[pl]..[left[|left|-1]]]
        // so contributes for left-pl cross-inversions
        if (pr == right.size()){
            a[idx++] = left[pl++];
        } else if (pl == left.size()){
            a[idx++] = right[pr++];
        } else {
            if (left[pl] < right[pr]){
                a[idx++] = left[pl++];
            } else {
                a[idx++] = right[pr++];
                total += left.size() - pl;
            }
        }
    }
    // cout << "l=" << l << " r=" << r << endl;
    // printmsg("segment=", a.begin()+l, a.begin()+r+1);
    // cout << "total=" << total << endl;
    return total;
}

i64 intersection_pairs(vector<pair<i64, i64>> v){
    // sort by start time
    // no two elements have same start time or same end time
    // since cuts don't meet at border
    sort(all(v));
    vector<i64> end;
    for (auto[a, b]: v){
        end.emplace_back(b);
    }
    // count inversions on end
    return inversions(end);
}

void solve(){
    i64 x, y;
    cin >> x >> y;
    i64 h, v;
    cin >> h >> v;

    vector<pair<i64, i64>> h_seg(h), v_seg(v);

    for (i64 i = 0; i < h; i++) cin >> h_seg[i].first >> h_seg[i].second;
    for (i64 i = 0; i < v; i++) cin >> v_seg[i].first >> v_seg[i].second;

    cout << (h + 1) * (v + 1) + intersection_pairs(h_seg) + intersection_pairs(v_seg) << endl;

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
