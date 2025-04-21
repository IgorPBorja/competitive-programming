
#define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
 
#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define print(first, last) for(auto it = first; it != last; it++){cerr << *it << "|";} cerr << endl;
#define printgraph(msg, G) cerr << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
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

const i64 INF = (i64)2e18;

void solve(){
    i64 n;
    cin >> n;
    string s;
    cin >> s;

    i64 a[n];
    pair<i64, i64> p[n - 1];
    map<pair<i64, i64>, vector<i64>> pos_p;

    i64 cur = 0;
    i64 c = 0;
    for (i64 i = 0; i < n; i++){
        a[i] = s[i] - '0';
        if (a[i] != cur){
            ++c;
            cur = a[i];
        }
        ++c;
    }
    for (i64 i = 0; i + 1 < n; i++){
        p[i] = make_pair(a[i], a[i + 1]);
        pos_p[p[i]].emplace_back(i);
    }

    i64 min_delta = 0; // no reversals

    // try reversing 0..r
    for (i64 r = 1; r < n; r++){
        i64 delta = - (a[0] != 0) + (a[r] != 0);
        if (r + 1 < n){
            delta += - (a[r] != a[r + 1]) + (a[0] != a[r + 1]);
        }
        min_delta = min(delta, min_delta);
    }

    // try reversing l..n-1
    for (i64 l = 1; l < n - 1; l++){
        i64 delta = - (a[l] != a[l - 1]) + (a[n - 1] != a[l - 1]);
        min_delta = min(delta, min_delta);
    }

    // try reversing l..r with l != 0 and r != n - 1
    // so a[l-1,l] = a[r,r+1] and a[l - 1] != a[l]
    for (i64 l = 1; l + 1 < n; l++){
        if (a[l - 1] != a[l]){
            // last pos
            i64 r = pos_p[make_pair(a[l - 1], a[l])].back();
            if (r > l){
                // 01 ... 01 ==> 00 ... 11 or 10 ... 10 ==> 11 ... 00
                min_delta = min(min_delta, (i64)(-2));
            }
        }
    }
    cout << c + min_delta << endl;
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

