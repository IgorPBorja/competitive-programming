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
NOTE: we suppose without loss of generality that all elements of a are distinct
and that a is sorted non-decreasing
(if not, just remove duplicates and sort it)

Lemma 1: the answer is 1 step iff gcd({a[i + 1] - a[i]: 0 <= i < n - 1}) > 1

Proof: Let d be this gcd.
=> If the answer is 1, there exists m > 1 and some x such that
a[i] = x mod m for all i, so a[i + 1] - a[i] is divisible by m for all i.

<= If d > 1, then a[n - 1] = a[n - 2] = ... = a[0] mod m
*/

/*
Lemma 2: The answer is always at most 2

Proof: trivial (as M = 2 is a candidate to solve the problem in at most two steps)
*/

/*
Lemma 3: Let M = max(a) and N = size(a). Then any solution for a in two steps
is at most 2M/N.

Proof: Let m be a solution and k = M/m. Then we have 2 options for remainders
and k quotient options, and we must have 2k >= N to cover all values. Therefore
2M/m >= N ==> m <= 2M/N
*/

/*
If N >= 3, then either the sequence starts out as x x ...
or x y x ...
or x y y ...
Therefore, m is a divisor of either a[1] - a[0], a[2] - a[0] or a[2] - a[1],
so, there is a algorithm in O(N max(i=1..M)div(i) + 3 * sqrt(M)) = O(N * M^{1/3} + sqrt(M))

If N = 2, and there is no solution in 1 step, then any 1 < m <= M is a solution.

Maybe an extra log factor just to check duplicates on the divisors checked,
so O(N M^{1/3}log M)
*/

set<i64> divisors(i64 x){
    set<i64> s;
    for (i64 i = 1; i * i <= x; i++){
        if (x % i == 0) {
            s.emplace(i);
            if (i != x / i) s.emplace(x / i);
        }
    }
    s.erase(1);
    return s;
}

void solve(){
    const i64 M = (i64)1e9;

    i64 _n;
    set<i64> _s;
    cin >> _n;
    for (i64 i = 0; i < _n; i++){
        i64 x;
        cin >> x;
        _s.insert(x);
    }

    const i64 n = _s.size();
    vector<i64> a(n);
    copy(all(_s), a.begin());
    sort(all(a));

    // check for solution in 1 step
    if (n == 1){
        cout << 1 << " ";
        // any 1 < m <= M is a solution
        cout << M - 1 << endl;
        return;
    }
    i64 g = 0;
    for (i64 i = 0; i + 1 < n; i++){
        g = __gcd(g, a[i + 1] - a[i]);
    }
    if (g > 1){
        cout << 1 << " ";
        cout << divisors(g).size() << endl;
    } else {
        // any 1 < m <= M is a solution
        cout << 2 << " ";
        if (n == 2){
            cout << M - 1 << endl;
        } else {
            // do inclusion-exclusion
            i64 d1 = a[1] - a[0];
            i64 d2 = a[2] - a[0];
            i64 d3 = a[2] - a[1];
            set<i64> s1 = divisors(d1), s2 = divisors(d2), s3 = divisors(d3);
            s1.merge(s2);
            s1.merge(s3);
            i64 ans = 0;
            for (i64 d: s1){
                i64 r1 = -1, r2 = -1;
                bool ok = true;
                for (i64 i = 0; i < n; i++) {
                    i64 rem = a[i] % d;
                    if (r1 == -1) r1 = rem;
                    else if (rem != r1){
                        if (r2 == -1) r2 = rem;
                        else if (rem != r2){
                            // third unique remainder
                            ok = false;
                            break;
                        }
                    }
                }
                if (ok) ++ans;
            }
            cout << ans << endl;
        }
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
