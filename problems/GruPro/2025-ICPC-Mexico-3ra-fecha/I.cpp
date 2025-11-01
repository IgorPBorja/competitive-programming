// #define TESTCASES

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

/*
Each A[i]B[j] appears only once on k = i mod j
ANS = sum(i)sum(j) (i mod j) A[i]B[j] = sum(i)sum(j) (i - floor(i/j)j) A[i]B[j]
    = (sum(j) B[j]) * (sum(i) i A[i]) - sum(j) j * B[j] * (sum(i) floor(i/j)A[i])

The first element is a constant
For the second, for each j there are n/j+1 distinct values for floor(i/j)
and each happens over a contiguous range of i indices. Final complexity is O(m + n log n)
*/

void solve(){
    // result might be as large as n * m * MAX(A) * MAX(B) * m
    // since in a worst-case scenario 
    // we need i128
    i64 _n, _m;
    cin >> _n >> _m;
    i128 n = _n, m = _m;

    vector<i128> A(n + 1, 0), B(m + 1, 0);
    i128 sb = 0, weighted_sa = 0;
    vector<i128> prefA(n + 1, 0);  // prefA[i] = A[1] + ... + A[i]
    for (i128 i = 1; i <= n; i++) {
        i64 x;
        cin >> x;
        A[i] = x;
        weighted_sa += i * A[i];
        prefA[i] = prefA[i - 1] + A[i];
    }
    for (i128 j = 1; j <= m; j++) {
        i64 x;
        cin >> x;
        B[j] = x;
        sb += B[j];
    }

    i128 ans = sb * weighted_sa;
    for (i128 j = 1; j <= m; j++){
        i128 w = j * B[j];
        for (i128 d = 1; d <= n / j; d++) {  // d = 0 does not matter, since weight is 0
            i128 l = d * j, r = min(d * j + j - 1, n);
            if (l <= r){
                ans -= w * d * (prefA[r] - prefA[l - 1]);
            }
        }
    }
    if (ans == 0){
        cout << 0 << endl;
        return;
    }
    vector<int> digits;
    while (ans > 0){
        digits.emplace_back(ans % (i128)10);
        ans /= (i128)10;
    }
    reverse(all(digits));
    for (auto c: digits) cout << c;
    cout << endl;
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
