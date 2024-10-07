// #define TESTCASES
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

const int B = 30;
const int MAXN = (int)2e5 + 10;

i64 min_xor(const vector<int>& a, int l1, int r1, int l2, int r2, const int pos){
    // each range is guaranteed to have all bits with position > pos fixed
    if (pos < 0){
        return 0;
    }
    vector<int> la, lb, ra, rb;
    int m1 = l1, m2 = l2;
    while (m1 <= r1 && (a[m1] & (1ll << pos)) == 0) ++m1;
    while (m2 <= r2 && (a[m2] & (1ll << pos)) == 0) ++m2;
    
    if (l1 < m1 && m1 <= r1 && l2 < m2 && m2 <= r2){
        return min(min_xor(a, l1, m1 - 1, l2, m2 - 1, pos - 1), min_xor(a, m1, r1, m2, r2, pos - 1));
    } else if (l1 < m1 && l2 < m2){
        return min_xor(a, l1, m1 - 1, l2, m2 - 1, pos - 1);
    } else if (m1 <= r1 && m2 <= r2){
        return min_xor(a, m1, r1, m2, r2, pos - 1);
    } else if (l1 < m1 && m2 <= r2){
        return min_xor(a, l1, m1 - 1, m2, r2, pos - 1) + (1ll << pos);
    } else if (m1 <= r1 && l2 < m2){
        return min_xor(a, m1, r1, l2, m2 - 1, pos - 1) + (1ll << pos);
    } else {
        throw std::runtime_error("unexpected");
    }
}

// O(N * sum(b <= B)) = O(N * B^2) with small constant
i64 mst(const vector<int>& a, int l, int r, int b = B - 1){
    if (b < 0 || l >= r){
        return 0;
    }
    // find first with active bit b
    int m = l;
    while (m <= r && (a[m]&(1ll << b)) == 0) ++m;
    // now it is guaranteed two halves have same bit value at position b
    i64 w1 = mst(a, l, m - 1, b - 1), w2 = mst(a, m, r, b - 1);
    
    vector<int> left(m - l), right(r + 1 - m);
    for (int i = l; i < m; i++) left[i - l] = a[i];
    for (int i = m; i <= r; i++) right[i - m] = a[i];
    if (l < m && m <= r){
        // O(N * b)
        return (1ll << b) + min_xor(a, l, m - 1, m, r, b - 1) + w1 + w2;
    } else {
        return w1 + w2;
    }
}

void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    cout << mst(a, 0, n - 1) << endl;
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
