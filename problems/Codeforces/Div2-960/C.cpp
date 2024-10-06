// UNSOLVED

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

vector<i64> mad(const vector<i64> &a){
    const i64 n = a.size();
    map<i64, i64> first;
    for (i64 i = 0; i < n; i++){
        if (first.find(a[i]) == first.end()){
            first[a[i]] = i;
        }
    }
    vector<i64> b(n);
    b[0] = 0;
    for (i64 i = 1; i < n; i++){
        if (a[i] > b[i - 1] && i != first[a[i]]){
            b[i] = a[i];
        } else {
            b[i] = b[i - 1];
        }
    }
    return b;
}

void solve(){
    i64 n;
    cin >> n;

    vector<i64> a(n);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }
    i64 ans = 0;
    for (i64 x: a) ans += x;

    vector<i64> b = mad(a);
    vector<i64> occur, distinct;
    i64 cnt = 1, val = b[0];
    for (i64 i = 1; i < n; i++){
        if (b[i] > val){
            occur.emplace_back(cnt);
            distinct.emplace_back(val);
            cnt = 1;
            val = b[i];
        } else {
            ++cnt;
        }
    }
    occur.emplace_back(cnt);
    distinct.emplace_back(val);

    const i64 k = occur.size();
    vector<i64> suf(k + 1);
    suf[k] = 0;
    for (i64 i = k - 1; i >= 0; i--){
        suf[i] = occur[i] + suf[i + 1];
    }

    for (i64 i = 0; i < k; i++){
        ans += distinct[i] * (occur[i] * (suf[i + 1] - (k - i - 1)) + (occur[i] * (occur[i] + 1)) / 2);
    }
    cout << ans << endl;
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
