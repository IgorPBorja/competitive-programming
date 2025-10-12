#define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
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

/*
triangle inequality: a + b > c
by repeatedely using the inequality on a n-gon
a1 + a2 + ... + a[n - 1] > a[n]

and that is (should be?) enough to guarantee existence of a n-gon with these side lengths
*/

void solve(){
    i64 n;
    cin >> n;
    vector<i64> a(n);
    map<i64, i64> cnt;
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        ++cnt[a[i]];
    }

    i64 p = 0;
    vector<i64> unpaired;
    i64 sides = 0;
    for (auto[k, c]: cnt){
        // you can always put k twice
        // since whathever + k > k
        p += 2 * (c / 2) * k;
        sides += 2 * (c / 2);
        if (c % 2) unpaired.emplace_back(k);
    }
    sort(all(unpaired));
    i64 ans = (sides >= 3 ? p : 0);

    // try to put only one extra element (unpaired)
    // we need p > x and the maximum x possible
    for (i64 x: unpaired){
        if (p > x && sides >= 2){ // triangle inequality met, and at least 3 sides
            ans = max(ans, p + x);
        }
    }

    // try to put 2 unpaired (distinct)
    // we need unpaired[l] + p > unpaired[r] with l < r
    // so greedily we take unpaired[r - 1] for each r
    // (NOTE: only the r values where unpaired[r] - unpaired[r - 1] < p work)
    for (i64 r = 1; r < (i64)unpaired.size(); r++){
        if (unpaired[r - 1] + p > unpaired[r] && sides > 0){
            ans = max(ans, p + unpaired[r - 1] + unpaired[r]);
        }
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
