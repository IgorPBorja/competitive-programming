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

/*

*/

const i64 MOD = (i64)998244353;

i64 bexp(i64 a, i64 p){
    if (p == 0) return 1;
    else {
        i64 b = bexp(a, p / 2);
        i64 b2 = (b * b) % MOD;
        if (p % 2 == 0) return b2;
        else return (a * b2) % MOD;
    }
}

i64 inv(i64 a) { return bexp(a, MOD - 2); }

/*
Let the segments have lenghts s1...s_k (all odd, since they are centered at some tower).
Then binary mask of active towers is **unique/forced** (only the centers of the segments are active),
which has probability of 1/2^n.

So answer for n is #{number of ways to write n as sum of odd numbers}/2^n

Let f(n) = #{number of ways to write n as sum of odd numbers}

Then:

if n=2k+1 is odd: last segment might be of length 1, 3, 5,...,2k-1,2k+1
==> f(2k+1) = sum(i=0..k)f(2k+1-(2i+1)) = sum(i=0..k)f(2(k-i)) = sum(i=0..k)f(2i)

if n=2k is even: last segment might be of length 1, 3, ..., 2k-1
==> f(2k) = sum(i=0..k-1)f(2k-(2i+1)) = sum(i=0..k-1)f(2(k-i) - 1) = sum(i=1..k)f(2i - 1)
= sum(i=0..k-1)f(2i + 1)

Notice then that
f(2k + 1) = sum(i=0..k)f(2i) = sum(i=0..k-1)f(2i) + f(2k) = f(2k-1) + f(2k)
and similarly f(2k) = f(2k-1) + f(2k-2). So f is fibonacci. Answer is then Fib(n)/2^n
where Fib(0) = 0 and Fib(1) = 1
*/

void solve(){
    i64 n;
    cin >> n;
    vector<i64> fib(n + 1);
    fib[0] = 0;  // empty set of targets, always possible
    fib[1] = 1;

    for (i64 i = 2; i <= n; i++){
        fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;
    }
    cout << (fib[n] * inv(bexp(2, n))) % MOD << endl;
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

