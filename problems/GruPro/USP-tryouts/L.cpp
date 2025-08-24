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

const i64 INF = (i64)1e18;
const i64 MOD = (i64)1e9 + 7;

// O(N^4 * log K)

inline i64 project(i64 i, i64 j, i64 N){
    return i * N + j;
}

vector<vector<i64>> matmul_Z2(vector<vector<i64>> A, vector<vector<i64>> B){
    i64 n = A.size(), m = B[0].size(), p = B.size();
    vector<vector<i64>> C(n, vector<i64>(m));
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            C[i][j] = 0;
            for (i64 k = 0; k < p; k++){
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % 2;
            }
        }
    }
    return C;
}

vector<vector<i64>> bexp(vector<vector<i64>> A, i64 p){
    i64 n = A.size();
    if (p == 0){
        vector<vector<i64>> id(n, vector<i64>(n));
        for (i64 i = 0; i < n; i++) id[i][i] = 1;
        return id;
    } else {
        vector<vector<i64>> B = bexp(A, p / 2);
        vector<vector<i64>> B2 = matmul_Z2(B, B);
        if (p % 2 == 0){
            return B2;
        } else {
            return matmul_Z2(B2, A);
        }
    }
}

void solve(){
    i64 n, k;
    cin >> n >> k;
    vector<vector<i64>> a(n, vector<i64>(n));
    vector<vector<i64>> bad(n, vector<i64>(n));
    for (i64 i = 0; i < n; i++){
        string s;
        cin >> s;
        for (i64 j = 0; j < n; j++){
            if (s[j] == '#'){
                bad[i][j] = true;
                a[i][j] = 0;
            } else if (s[j] == '0'){
                a[i][j] = 0;
            } else {
                a[i][j] = 1;
            }
        }
    }

    vector<vector<i64>> M(n * n, vector<i64>(n * n));
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < n; j++){
            if (bad[i][j]) continue;  // row is 0
            for (i64 dx = -1; dx <= 1; dx++){
                for (i64 dy = -1; dy <= 1; dy++){
                    i64 ni = i + dx, nj = j + dy;
                    if (ni < 0 || ni >= n || nj < 0 || nj >= n) continue;
                    i64 c1 = project(i, j, n), c2 = project(ni, nj, n);
                    M[c1][c2] = 1;
                }
            }
        }
    }
    // printgraph("M=", M);

    vector<vector<i64>> Mk = bexp(M, k);
    vector<i64> ans(n * n);
    for (i64 i = 0; i < n * n; i++){
        ans[i] = 0;
        for (i64 j = 0; j < n * n; j++){
            ans[i] = (ans[i] + Mk[i][j] * a[j / n][j % n]) % 2;
        }
    }
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < n; j++){
            if (bad[i][j]){
                cout << '#';
            } else {
                i64 c = project(i, j, n);
                cout << ans[c];
            }
        }
        cout << endl;
    }
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
