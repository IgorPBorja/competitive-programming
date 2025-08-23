#define TESTCASES
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
    string s;
    cin >> s;
    const i64 n = s.size();

    vector<i64> open_p, closed_p, open_c, closed_c;
    for (i64 i = 0; i < n; i++){
        if (s[i] == '(') {
            open_p.emplace_back(i);
        } else if (s[i] == ')'){
            closed_p.emplace_back(i);
        } else if (s[i] == '['){
            open_c.emplace_back(i);
        } else if (s[i] == ']'){
            closed_c.emplace_back(i);
        }
    }

    i64 pairs = 0;
    i64 op = 0, cl = 0;
    while (op < open_p.size() && cl < closed_p.size()){
        while (cl < closed_p.size() && closed_p[cl] < open_p[op]){
            ++cl;
        }
        if (op < open_p.size() && cl < closed_p.size()){
            ++pairs;
            ++op;
            ++cl;
        }
    }
    op = 0, cl = 0;
    while (op < open_c.size() && cl < closed_c.size()){
        while (cl < closed_c.size() && closed_c[cl] < open_c[op]){
            ++cl;
        }
        if (op < open_c.size() && cl < closed_c.size()){
            ++pairs;
            ++op;
            ++cl;
        }
    }
    cout << pairs << endl;
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

