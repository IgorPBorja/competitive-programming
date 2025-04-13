// #define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
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

const i64 INF = (i64)2e18;

vector<i64> kmp(vector<i64> a){
    const i64 n = a.size();
    vector<i64> pi(n, 0);
    // pi[i] = max{k: pi[0..k-1] = pi[i-k+1...i], such that k < i + 1}
    pi[0] = 0;
    for (i64 i = 1; i < n; i++){
        // if you have k, a[0..k-1] = a[i-k..i-1]
        // then k=>pi[k-1]
        i64 k = pi[i - 1];
        while (k > 0 && a[k] != a[i]){
            k = pi[k - 1];
        }
        if (a[k] == a[i]) ++k;
        pi[i] = k;
    }
    return pi;
}

void solve(){
    i64 n, w;
    cin >> n >> w;
    vector<i64> a(n), b(w);
    vector<i64> s(n + w - 1);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }
    for (i64 i = 0; i < w; i++){
        cin >> b[i];
    }
    if (w == 1){
        // can see everywhere
        cout << n << endl;
        return;
    }

    for (i64 i = 0; i < w - 1; i++){
        s[i] = b[i + 1] - b[i];
    }
    s[w - 1] = INF; // symbol
    for (i64 i = 0; i < n - 1; i++){
        s[w + i] = a[i + 1] - a[i];
    }
    // printmsg("s=", s.begin(), s.end());
    vector<i64> pi = kmp(s);
    // printmsg("pi=", pi.begin(), pi.end());
    i64 cnt = 0;
    // w..w+(w-2)
    for (i64 i = w + (w - 2); i < s.size(); i++){
        // s[i-w+2...i] = s[0..w-2]
        if (pi[i] >= w - 1){
            ++cnt;
        }
    }
    cout << cnt << endl;
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
