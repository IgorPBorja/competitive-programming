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

i64 apply(i64 x, i64 y){
    i64 z = x + 1;
    while (z % y == 0){
        z /= y;
    }
    return z;
}

const i64 MAXN = 1e6;

inline i64 ceil(i64 a, i64 b){
    return (a + b - 1) / b;
}

void solve(){
    i64 x, y, k;
    cin >> x >> y >> k;

    i64 i = 0;
    unordered_map<i64, i64> appeared;
    i64 cycle_size = 0;
    while (i + 1 <= k){
        // compress initial operations
        i64 diff = min(ceil(x, y) * y - 1 - x, k - i);
        if (diff > 0){
            x += diff;
            i += diff;
            if (i == k) break;
        }

        x = apply(x, y);
        ++i;
        if (appeared.find(x) != appeared.end()){
            cycle_size = i - appeared[x];
            break;
        } else {
            appeared[x] = i;
        }
    }
    if (cycle_size > 0){
        i += ((k - i) / cycle_size) * cycle_size;
    }
    while (i + 1 <= k){
        // compress initial operations
        i64 diff = min(ceil(x, y) * y - 1 - x, k - i);
        if (diff > 0){
            x += diff;
            i += diff;
            if (i == k) break;
        }

        x = apply(x, y);
        ++i;
    }
    cout << x << endl;
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
