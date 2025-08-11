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

bool cmp_map(const map<i64, i64>& base, map<i64, i64>& target){
    for (auto[k, v]: base){
        if (v != target[k]) return false;
    }
    return true;
}

void solve(){
    string s, base;
    cin >> s >> base;
    const i64 n = s.size(), m = base.size();

    vector<i64> mapping(26, -1);

    vector<vector<i64>> pos_per_letter_base(26);
    vector<vector<i64>> pos_per_letter(26);

    for (i64 i = 0; i < m; i++){
        i64 x = base[i] - 'A';
        pos_per_letter_base[x].emplace_back(i);
    }
    for (i64 i = 0; i < n; i++){
        i64 x = s[i] - 'A';
        pos_per_letter[x].emplace_back(i);
    }


    // eliminate positions
    vector<i64> ok_starts(n - m + 1, 1);
    for (i64 c = 0; c < 26; c++){
        for (i64 p: pos_per_letter_base[c]){
            for (i64 q: pos_per_letter[c]){
                // we can't have i+p == q
                // so q-p is invalid. Also q-p <= m
                if (q < p || q-p > n-m) continue;
                ok_starts[q-p] = false;
            }
        }
    }

    cout << accumulate(ok_starts.begin(), ok_starts.end(), 0ll) << endl;
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
