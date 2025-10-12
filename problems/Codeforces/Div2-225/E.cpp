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
    const i64 B = 24;
    vector<i64> sos(1ll << 24, 0);

    i64 n;
    cin >> n;
    for (i64 i = 0; i < n; i++){
        string w;
        cin >> w;
        i64 c[3] = {w[0] - 'a', w[1] - 'a', w[2] - 'a'};
        i64 msk = (1ll << c[0]) | (1ll << c[1]) | (1ll << c[2]);
        ++sos[msk];
    }
    for (i64 i = 0; i < B; i++){
        // different up to 2^i
        for (i64 msk = (1ll << B) - 1; msk >= 0; msk--){
            if (msk & (1ll << i)){  // can differ at 2^i and be submask
                sos[msk] += sos[msk ^ (1ll << i)];
            }
        }
    }

    i64 ans = 0;
    for (i64 vowel_set = 0; vowel_set < (1ll << B); vowel_set++){
        // #(w_i: w_i has at least one vowel for this vowel set)
        // = #(w_i: w_i & vowel_set != 0)
        // = n - #(w_i: w_i & vowel_set == 0)
        // = n - #(w_i: w_i is submask of ~vowel_set)
        i64 partial = n - sos[((1ll << B) - 1) ^ vowel_set];
        ans ^= (partial * partial);
    }
    cout << ans << endl;
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
