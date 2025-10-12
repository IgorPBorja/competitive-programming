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
#define print(msg, v) debug << msg; for(auto it = v.begin(); it != v.end(); it++){debug << *it << " ";} debug << endl;
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

void solve(){
    vector<tuple<i64, i64, i64>> left, top, right, bottom;
    i64 w, h;
    cin >> w >> h;

    auto add_point = [&](i64 x, i64 y, i64 i){
        if (x == 0 && y < h) left.emplace_back(x, y, i);
        else if (x < w && y == h) top.emplace_back(x, y, i);
        else if (x == w && y > 0) right.emplace_back(x, y, i);
        else if (x > 0 && y == 0) bottom.emplace_back(x, y, i);
    };
    auto in_border = [&](i64 x, i64 y){
        return (x == 0 || x == w || y == 0 || y == h);
    };
    i64 n;
    cin >> n;
    for (i64 i = 0; i < n; i++){
        i64 x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (in_border(x1, y1) && in_border(x2, y2)){
            add_point(x1, y1, i);
            add_point(x2, y2, i);
        }
    }
    sort(all(left), [](auto p, auto q){
        return get<1>(p) < get<1>(q);
    });
    sort(all(top), [](auto p, auto q){
        return get<0>(p) < get<0>(q);
    });
    sort(all(right), [](auto p, auto q){
        return get<1>(p) > get<1>(q);
    });
    sort(all(bottom), [](auto p, auto q){
        return get<0>(p) > get<0>(q);
    });
    
    vector<tuple<i64, i64, i64>> full;
    full.reserve(left.size() + top.size() + right.size() + bottom.size());
    for (auto p: left){
        full.emplace_back(p);
    }
    for (auto p: top){
        full.emplace_back(p);
    }
    for (auto p: right){
        full.emplace_back(p);
    }
    for (auto p: bottom){
        full.emplace_back(p);
    }
    vector<i64> seen(n);
    vector<i64> stack;
    for (auto[x, y, i]: full){
        // cout << "Pt x=" << x << " y=" << y << " i=" << i << endl;
        if (!seen[i]){
            stack.emplace_back(i);
            seen[i] = true;
        } else {
            if (stack.empty() || stack.back() != i){
                cout << "N" << endl;
                return;
            }
            stack.pop_back();
        }
    }
    cout << "Y" << endl;
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
