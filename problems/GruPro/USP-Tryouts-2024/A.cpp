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

void solve(){
    i64 n;
    cin >> n;

    vector<tuple<i64, i64, i64, i64>> events(n);  // t, m, c
    for (i64 i = 0; i < n; i++){
        i64 t, m, c;
        cin >> t >> m >> c;
        // all t_i are distinct
        events[i] = make_tuple(t, c, m, i);
    }
    
    vector<i64> sad;
    set<tuple<i64, i64, i64, i64>> pq;
    for (auto[t, c, m, i]: events){
        pq.emplace(t, c, m, i);
    }
    queue<pair<i64, i64>> postponed;
    bool active = false;
    i64 active_idx = -1;
    i64 active_end_time = -1;
    while (!pq.empty()){
        auto[t, c, m, i] = *pq.begin();
        pq.erase(pq.begin());
        if (c == -1){
            // closing
            active = false;
            // can put a postponed event now
            if (!postponed.empty()){
                auto[j, delta] = postponed.front();
                postponed.pop();
                pq.emplace(t + delta, -1, 0, j);
                active_idx = j;
                active_end_time = t + delta;
                active = true;
            }
            // cout << "closed" << endl;
        } else if (!active){
            // immediately put
            pq.emplace(t + m, -1, 0, i);
            active_idx = i;
            active_end_time = t + m;
            active = true;
            // cout << "immediately put" << endl;
        } else if (c == 0){
            // postpone
            postponed.emplace(i, m);
            // cout << "postponed" << endl;
        } else {
            // interrupt
            sad.emplace_back(active_idx);
            pq.erase(make_tuple(active_end_time, -1, 0, active_idx));
            pq.emplace(t + m, -1, 0, i);
            active_idx = i;
            active_end_time = t + m;
            // cout << "interrupted" << endl;
        }
    }
    cout << sad.size() << endl;
    for (i64 f: sad){
        cout << f + 1 << " ";
    }
    cout << endl;
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
