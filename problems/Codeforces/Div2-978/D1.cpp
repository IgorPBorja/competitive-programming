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

const i64 INF = 2e9;

void solve(){
    i64 n;
    cin >> n;
    for (i64 i = 0; i < n - 1; i += 2){
        i64 r1, r2;
        cout << "? " << i + 1 << " " << i + 2 << endl;
        cout.flush();
        cin >> r1;
        cout << "? " << i + 2 << " " << i + 1 << endl;
        cout.flush();
        cin >> r2;
        if (r1 != r2){
            // one of those is the imposter
            // try an alternative query for i and i + 1
            i64 other = (i != 0) ? i : 3;
            i64 r3, r4;
            cout << "? " << i + 1 << " " << other << endl;
            cout.flush();
            cin >> r3;
            cout << "? " << other << " " << i + 1 << endl;
            cout.flush();
            cin >> r4;
            if (r3 != r4) {
                cout << "! " << i + 1 << endl;
            } else {
                cout << "! " << i + 2 << endl;
            }
            cout.flush();
            return;
        }
    }
    if (n % 2 == 1){
        cout << "! " << n << endl;
        cout.flush();
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

