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

int main(){
	i64 MAXN;
	cin >> MAXN;

	i64 dp[MAXN + 1];
	vector<i64> cnt(MAXN + 1, 0);
	
    // O(N^{3/2} * log(sqrt N))
	for (i64 n = 0; n <= MAXN; n++){
		set<i64> s;
		for (i64 i = 1; i * i <= n; i++){
            s.emplace(dp[n - i * i]);
		}
		i64 mex = 0;
		for (i64 x: s){
            if (x != mex) break;
            else ++mex;
		}
		dp[n] = mex;
	}

	// cout << endl;
	// for (i64 i = 0; i <= MAXN; i++) cout << setw(3) << i << " ";
	// cout << endl;
	// for (i64 i = 0; i <= MAXN; i++) cout << setw(3) << dp[i] << " ";
	// cout << endl;

    // can't be losing if exactly two piles are losing
    // m is O(sqrt(n)) since each n sees O(sqrt(n)) neighbors
    i64 m = 0;
    for (i64 i = 0; i <= MAXN; i++){
        m = max(m, dp[i]);
    }
    assert(m <= MAXN);
    vector<vector<i64>> grundy(m + 1);
    for (i64 i = 0; i <= MAXN; i++) {
        grundy[dp[i]].emplace_back(i);  // already sorted (each)
    }
    // division by grundy number forms partition

    // for each xor pair a^b it is active only cnt[a^b] times
    // since we need c = a^b for xor 0
    i64 losing = 0;
    for (i64 i = 0; i <= m; i++){
        for (i64 j = 0; j <= m; j++){
            if ((i ^ j) <= m){
                // try to pick a with g(a) = i, b with g(b) = j, c with g(c) = i ^ j
                // such that a <= b <= c
                
                // let A = grundy[i], B = grundy[j], C = grundy[i ^ j]
                // for that, precompute largerB[i] = {x in C, x > B[i]} using two-pointers
                // then suffix-sum that and compute largerA[i] = {j: B[k] >= A[i] for all k >= j}

                const vector<i64> &A = grundy[i], &B = grundy[j], &C = grundy[i ^ j];

                vector<i64> largerB(B.size() + 1, 0);
                i64 r = 0;
                for (i64 l = 0; l < B.size(); l++){
                    while (r < C.size() && C[r] < B[l]) ++r;
                    // now C[r] >= B[l]
                    largerB[l] = C.size() - r;   // r..C.size()-1
                }
                // suffix sum
                for (i64 l = B.size() - 1; l >= 0; l--){
                    largerB[l] += largerB[l + 1];
                }

                vector<i64> largerIndexA(A.size());
                r = 0;
                for (i64 l = 0; l < A.size(); l++){
                    while (r < B.size() && B[r] < A[l]){
                        ++r;
                    }
                    // now B[r] >= A[l] and r is minimal
                    largerIndexA[l] = r;
                }
                i64 subtotal = 0;
                for (i64 i = 0; i < A.size(); i++){
                    subtotal += largerB[largerIndexA[i]];
                }
                // cout << "subtotal=" << subtotal << endl;
                losing += subtotal;
            }
        }
    }
    cout << losing << endl;
}
