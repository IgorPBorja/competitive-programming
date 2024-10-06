// #define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vvi vector<vector<int>>
#define vvb vector<vector<bool>>
#define vvc vector<vector<char>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define eb emplace_back
#define ep emplace
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
 
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define print(first, last) for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
 
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

const i64 MOD = (i64)1e9 + 7;

template<typename T>
void print_matrix(vector<vector<T>> m, const int width = 3){
    for (const vector<T>& row: m){
        for (const T& e: row){
            cout << setw(width) << e << " ";
        }
        cout << endl;
    }
}

vector<vector<i64>> matmul(vector<vector<i64>> &A, vector<vector<i64>> &B){
    assert(A[0].size() == B.size());
    vector<vector<i64>> C(A.size(), vector<i64>(B[0].size(), 0));
    for (size_t i = 0; i < A.size(); i++){
        for (size_t j = 0; j < B[0].size(); j++){
            for (size_t k = 0; k < B.size(); k++){
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

vector<vector<i64>> bexp(vector<vector<i64>> &A, i64 p){
    if (p == 0){
        vector<vector<i64>> Id(A.size(), vector<i64>(A[0].size(), 0));
        for (size_t i = 0; i < A.size(); i++){
            Id[i][i] = 1;
        }
        return Id;
    } else {
        vector<vector<i64>> M = bexp(A, p / 2);
        // print_matrix(M); cout << endl;
        vector<vector<i64>> M2 = matmul(M, M);
        // print_matrix(M2); cout << endl;
        if (p % 2 == 0){
            return M2;
        } else {
            return matmul(A, M2);
        }
    }
}

i64 L1(vector<vector<i64>> &M){
    i64 ans = 0;
    for (size_t i = 0; i < M.size(); i++){
        for (size_t j = 0; j < M[i].size(); j++){
            ans = (ans + M[i][j]) % MOD;
        }
    }
    return ans;
}

void solve(){
    i64 n, k;
    cin >> n >> k;

    vector<vector<i64>> adj(n, vector<i64>(n));
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < n; j++){
            cin >> adj[i][j];
        }
    }
    vector<vector<i64>> k_adj = bexp(adj, k);
    // print_matrix(k_adj);
    cout << L1(k_adj) << endl;
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
