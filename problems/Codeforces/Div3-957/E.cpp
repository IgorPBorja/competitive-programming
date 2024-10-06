#define TESTCASES
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
#define printgraph(msg, G) cout << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
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

// n * a (as str) = n + 10^d * n + 10^(2d) * n + ... + 10^((a - 1) * d) * n = (10^(ad) - 1) / (10^d - 1) * n
// where d = len(n)
// (n * a - b) (as str) = ((10 ^ ad - 1) / (10^d - 1) * n) / 10^b
// and length is a * len(n) - b
// which equals len(an - b) <= len(a) + len(n) + 1
// ==> a <= [len(a) + len(n) + 1 + b] / len(n) = 7 + b since len(a) <= 5
// since a is <= 1e4 we can just brute force it on the length check

/*
Let f(a, b) = a * STR(n) - b
Then f(a, b + 1) <= 0.1 * f(a, b)
which decreases a lot faster then 1 by 1

so do binary search on b given a
*/

const i64 MAX_A = 1e4;

i64 bexp(i64 a, i64 p){
    if (p == 0){
        return 1;
    } else {
        const i64 m = bexp(a, p / 2);
        if (p % 2 == 1){
            return m * m * a;
        } else {
            return m * m;
        }
    }
}

void solve(){
    i64 n;
    cin >> n;
    auto len = [](i64 x){
        i64 l = 0;
        while (x > 0){
            x /= 10;
            ++l;
        }
        return l;
    };

    const i64 ln = len(n);

    auto f = [&n, &ln](const i64 a, const i64 b){
        // will exclude (b / ln) repetitions of n and
        // will exclude the value of the last b % ln digits
        // shouldn't overflow this way
        if (a * ln - b <= 0){
            // empty string: INVALID!
            return (i64)(-1);
        }
        i64 rep = a - (b / ln);
        i64 shift = (bexp((i64)10, rep * ln) - 1) / (bexp((i64)10, ln) - 1);
        return (shift * n) / bexp((i64)10, b % ln);
    };

    vector<pair<i64, i64>> pairs;
    for (i64 a = 1; a <= MAX_A; a++){
        i64 lb = 1, rb = min(MAX_A, n * a);        
        while (lb <= rb){
            const i64 b = lb + (rb - lb) / 2;
            if (a * ln - b > len(a * n - b)){
                lb = b + 1;
            } else {
                // a * ln - b is not too large, won't overflow
                const i64 val = f(a, b);
                if (val == a * n - b){
                    pairs.emplace_back(a, b);
                    break;
                } else {
                    rb = b - 1;
                }
            }
        }
    }
    sort(pairs.begin(), pairs.end());
    cout << pairs.size() << endl;
    for (const auto&[a,b]: pairs){
        cout << a << " " << b << endl;
    }
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
