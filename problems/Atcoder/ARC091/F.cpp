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

/**
 * Theorem: for a given k (such that you can only take floor(x/k) from x), the grundy number is
 * g(r) = 0 for r < k
 * g(kx) = x
 * g(kx + r) = gx(kx + r - x - 1)
 * 
 * 
 * Proof (sketch): it creates a sliding window, and at each transition kx-1 -> kx
 * the window size increase which explains how the MEX increases (we don't lose someone).
 * In other transitions, we lose the first outside the window, which has size x for kx + r.
 */

 /**
  Compression idea: calculation g_K(N)

  1. If K is small (K <= sqrt(N)), then either we know g(N) directly or we reduce
    N to N - floor(N) - 1 ~ N * (1 - 1/k)
    After k iterations, we have a factor of (1-1/k)^k which is approximately 1/e where e is euler's number
    We reduce until N < K^2, so we have ln(N/K^2) groups of K transitions. This is maximum at K = O(sqrt(N))
    with maximum O(sqrt(N))

  2. If K is large (K^2 > N) then we group transition

    First we calculate m = floor(N/K) + 1 and then we binary search how many transitions we can do this way
    until floor(N/K) changes - note not more than K transitions can be made subtracting m.

    Also, we have at most N/K decreases to m, so we have O(N/K log(K)). Since K > sqrt(N), then
    N/K is O(sqrt(N)) and final complexity on this case is O(sqrt(N) log(K))


  Final complexity is O(sum sqrt(A_i) log(K_i)) ≃ O(N sqrt(M) log(M)) where M = 1e9
  so ~ 200 * 3 * 10^4 * 30 ~ 1800 * 10^5 = 1.8e8, ok for 2 seconds
  */


// recursive grundy calculation
i64 grundy(i64 N, i64 K){
    if (N < K) return 0;
    else if (N % K == 0){
        return N / K;
    } else if (K * K <= N){
        return grundy(N - N / K - 1, K);
    } else {
        // group transactions
        i64 m = N / K;
        i64 max_transitions = 1;
        i64 l = 1, r = K;
        while (l <= r){
            const i64 mid = l + (r - l) / 2;
            const i64 N2 = N - mid * (m + 1);  // mid transactions subtracting m+1 = floor(N/K)+1
            if (N2 / K < m){
                r = mid - 1;
            } else {
                max_transitions = mid;
                l = mid + 1;
            }
        }
        // sanity-check: when doing max_transitions transitions, do we stumble onto a
        // multiple of K?
        // given r = N mod K
        // so we need to now if there is a u < max_transitions such that -u*(m+1) = r mod K
        // However, if there is such u then we do a transition KX -> KX - something
        // and floor(N/K) changes! So we know there is no such u
        return grundy(N - max_transitions * (m + 1), K);
    }
}

void solve(){
    i64 n;
    cin >> n;
    vector<i64> A(n), K(n);
    for (i64 i = 0; i < n; i++) cin >> A[i] >> K[i];

    i64 xorsum = 0;
    for (i64 i = 0; i < n; i++){
        xorsum ^= grundy(A[i], K[i]);
    }

    if (xorsum > 0){
        cout << "Takahashi" << endl;  // player 1 wins Nim
    } else {
        cout << "Aoki" << endl;  // player 2 wins Nim
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
